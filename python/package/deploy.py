# -*- coding: utf-8 -*-
"""
"""

import os
import shutil
from distutils.core import run_setup

version = "1.2.0"
packages = ["2sw", "Msw"]

for suffix in packages:
    dist_suffix = os.path.join("dist", suffix)
    try:
        shutil.rmtree(os.path.join("Aria", "SDK", "shared"))
    except:
        pass
    dll_src_name = f"aria_sdk_{suffix}.dll"
    dll_dst_name= "aria_sdk.dll"
    for arch in ["x86", "x64"]:
        os.makedirs(os.path.join("Aria", "SDK", "shared", "windows", arch))
        shutil.copy(os.path.join("..", "dlls", "win", arch, dll_src_name), os.path.join("Aria", "SDK", "shared", "windows", arch, dll_dst_name))
        run_setup("setup.py", ["sdist","--format=zip"])
        os.makedirs(os.path.join(dist_suffix), exist_ok = True)
        shutil.copy(os.path.join("dist", f"aria_sdk-{version}.zip"), dist_suffix)
        os.remove(os.path.join("dist", f"aria_sdk-{version}.zip"))

