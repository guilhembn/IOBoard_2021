import subprocess
Import("env")

#print(env.Dump())
script = env['PROJECT_DIR'] + "/generate.sh"

rc = subprocess.call(script)

