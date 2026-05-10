import os,re
root = r'c:\Users\qu1r30n\Documents\GitHub\SYSTEMA_QU1R30N'

c_files = []
for base in [os.path.join(root,'modelos'), os.path.join(root,'procesos')]:
 for d,_,fs in os.walk(base):
  for f in fs:
if f.endswith('.c'):
 c_files.append(os.path.join(d,f))

# solo archivos que incluyen CLASE o var_fun_GG para asegurar macros disponibles

def should_process(text):
 return ('CLASE_QU1R30N.h' in text) or ('var_fun_GG.h' in text)

sig_start_re = re.compile(r'^\s*(?:static\s+)?int\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(')
return_re = re.compile(r'^(\s*)return\s+(.+);\s*(//.*)?$')

changed_files = []

for path in c_files:
 with open(path,'r',encoding='utf-8') as f:
  lines = f.readlines()
 text = ''.join(lines)
 if not should_process(text):
  continue

 out = []
 in_int_func = False
 pending_sig = False
 brace_depth = 0
 sig_buffer = []

 for line in lines:
  if not in_int_func and not pending_sig:
if sig_start_re.search(line) and ';' not in line:
 pending_sig = True
 sig_buffer = [line]
 out.append(line)
 if '{' in line:
  in_int_func = True
  pending_sig = False
  brace_depth = line.count('{') - line.count('}')
 continue
out.append(line)
continue

  if pending_sig:
sig_buffer.append(line)
out.append(line)
if '{' in line:
 in_int_func = True
 pending_sig = False
 brace_depth = ''.join(sig_buffer).count('{') - ''.join(sig_buffer).count('}')
continue

  # dentro de funcion int
  m = return_re.match(line)
  if m and 'RETORNAR_MODELO_ESTANDAR' not in line and 'RETORNAR_PROCESO_ESTANDAR' not in line:
indent, expr, comment = m.group(1), m.group(2).strip(), (m.group(3) or '')
if 'modelos' in path:
 newline = f"{indent}RETORNAR_MODELO_ESTANDAR({expr});"
else:
 newline = f"{indent}RETORNAR_PROCESO_ESTANDAR({expr});"
if comment:
 newline += f" {comment}"
newline += "\n"
out.append(newline)
  else:
out.append(line)

  brace_depth += line.count('{') - line.count('}')
  if brace_depth <= 0:
in_int_func = False
pending_sig = False
brace_depth = 0

 new_text = ''.join(out)
 if new_text != text:
  with open(path,'w',encoding='utf-8') as f:
f.write(new_text)
  changed_files.append(path)

print('FILES_CHANGED', len(changed_files))
for p in changed_files:
 print(p.replace(root+'\\',''))
