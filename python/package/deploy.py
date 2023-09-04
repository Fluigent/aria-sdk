# -*- coding: utf-8 -*-
"""
"""

import os
import shutil
from distutils.core import run_setup

version = "1.2.0"

try:
    shutil.rmtree(os.path.join("Aria", "SDK", "shared"))
except:
    pass
dll_dst_name= "aria_sdk.dll"

for arch in ["x86", "x64"]:
    os.makedirs(os.path.join("Aria", "SDK", "shared", "windows", arch))
    shutil.copy(os.path.join("..", "dll", "win", arch, dll_dst_name), os.path.join("Aria", "SDK", "shared", "windows", arch, dll_dst_name))

run_setup("setup.py", ["sdist","--format=zip"])

