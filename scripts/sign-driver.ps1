param([string]$BuildDir = "build\windows\x64\release", [string]$RepoRoot = (Split-Path $PSScriptRoot -Parent))
$driver = Join-Path $RepoRoot "$BuildDir\probe_driver.sys"
if (-not (Test-Path $driver)) { throw "driver not found: $driver" }
$signArgs = @("sign", "--sha1", "--cert", "XINDA", "--tsa-time", "2013-01-01T00:00:00Z")
foreach ($cer in @("signer\certs\verisign-cscs-2010.cer", "signer\certs\verisign-g5-mcvr.cer")) { $signArgs += @("--chain", (Join-Path $RepoRoot $cer)) }
$signArgs += $driver
$exe = Join-Path $RepoRoot "signer\spcsign\spcsign.exe"
& $exe @signArgs
if ($LASTEXITCODE -ne 0) { throw "spcsign failed ($LASTEXITCODE)" }
Write-Host "signed: $driver ($((Get-Item $driver).Length) bytes)"
