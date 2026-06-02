$root   = Join-Path $PSScriptRoot "..\SISTEMA_QU1R30N"
$bin    = Join-Path $root "bin"
$out    = Join-Path $bin  "sistema_qu1r30n_debug.exe"
$gcc    = "C:\msys64\ucrt64\bin\gcc.exe"

if (!(Test-Path $bin)) {
    New-Item -ItemType Directory -Path $bin | Out-Null
}

# Liberar el exe si el depurador lo tiene bloqueado
$nombre = [System.IO.Path]::GetFileNameWithoutExtension($out)
Get-Process -Name $nombre -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
Start-Sleep -Milliseconds 300

$src = Get-ChildItem -Path $root -Recurse -Filter "*.c" | ForEach-Object { $_.FullName }

& $gcc -g "-I$root" $src -o $out

if ($LASTEXITCODE -eq 0) {
    Write-Output "BUILD OK -> $out"
} else {
    Write-Error "BUILD FALLO (exit $LASTEXITCODE)"
    exit $LASTEXITCODE
}
