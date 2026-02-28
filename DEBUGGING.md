# Guía de Depuración - SYSTEMA_QU1R30N

## Configuración completada ✅

La depuración ha sido configurada completamente para usar GDB con MSYS2.

### Archivos de configuración creados:
- `.vscode/launch.json` - Configuración del depurador
- `.vscode/tasks.json` - Tareas de compilación
- `.vscode/c_cpp_properties.json` - Propiedades de C/C++
- `.vscode/settings.json` - Configuración del workspace

## Cómo depurar

### Opción 1: Usar la interfaz de VS Code
1. **Presiona `Ctrl+Shift+D`** o ve a "Run and Debug" en la sidebar
2. Selecciona **"GDB: Depurar SISTEMA_QU1R30N"** en el dropdown
3. Presiona **F5** o click en el botón "Start Debugging"

Esto automáticamente:
- Compilará el proyecto con símbolos de debug (`-g3`)
- Iniciará GDB
- Abrirá una consola externa donde ves la salida del programa

### Opción 2: Compilar manualmente y depurar
```bash
# Compilar con debug
gcc -std=c11 -Wall -Wextra -g3 -O0 -I. $(find . -name '*.c') -o sistema_debug.exe

# Luego en VS Code: F5 (comenzará el debugging)
```

## Funciones de depuración disponibles

Una vez que hayas iniciado el debugging:
- **F10** - Step Over (siguiente línea)
- **F11** - Step Into (entrar en función)
- **Shift+F11** - Step Out (salir de función)
- **F5** - Continue/Resume ejecución
- **Shift+F5** - Stop debugging

## Breakpoints (Puntos de quiebre)

1. Haz click en el margen izquierdo del editor junto al número de línea
2. Aparecerá un punto rojo 🔴
3. El debugger se pausará cuando ejecute esa línea

### Ejemplo:
```c
int main() 
{
    inicializacion();  // ← Click aquí para poner breakpoint
    
    conmutador("op_tienda|ventas|ABC123|2|SucursalX");  // Se pausará aquí
    
    return 0;
}
```

## Inspeccionar variables

En la pestaña "Debug" (lado izquierdo):
- **Variables** - Muestra todas las variables locales en scope actual
- **Watch** - Agrega expresiones para monitorear
- **Call Stack** - Muestra la pila de llamadas
- **Breakpoints** - Lista todos los breakpoints

## Ejemplo de sesión de debugging

```
1. Poner breakpoint en SISTEMA_QU1R30N.c línea 70 (en main)
2. Presionar F5
3. Se abrirá consola y el programa iniciará
4. Se pausará en el breakpoint
5. En la pestaña "Variables" verás:
   - ejemplos[] = array de comandos
   - i = índice actual
6. Presionar F10 para ir línea por línea
7. Presionar F5 para continuar
8. Presionar Shift+F5 para detener
```

## Configuración de GDB

Si necesitas ajustar algo en GDB, edita `.vscode/launch.json`:
- `miDebuggerPath` - Ruta al ejecutable de gdb
- `program` - Ruta del ejecutable a depurar
- `stopAtEntry` - Si es true, pausa al iniciar main

Cualquier cambio en launch.json se aplicará la próxima vez que presiones F5.

## Solución de problemas

Si el debugging no funciona:

1. **Compilar manualmente primero:**
   ```bash
   gcc -std=c11 -Wall -Wextra -g3 -O0 -I. $(find . -name '*.c') -o sistema_debug.exe
   ```

2. **Verificar que existe el ejecutable:**
   ```bash
   ls -la sistema_debug.exe
   ```

3. **GDB puede estar haciendo timeout:**
   - Aumenta el timeout en launch.json agregando:
     ```json
     "stopAtEntry": false,
     "stopOnEntry": false
     ```

4. **Reinstalar extensión C/C++:**
   - Abre Extensions (Ctrl+Shift+X)
   - Busca "C/C++" (Microsoft)
   - Click en "Install"

---

**✅ Todo configurado. ¡Ahora puedes depurar presionando F5!**
