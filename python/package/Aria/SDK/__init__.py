import os
import sys
import platform
import pkg_resources

_is_64_bits = sys.maxsize > 2**32
_platform = sys.platform
_os_name = _platform.lower()
_machine = platform.machine()
_processor_arch = _machine.lower()
_is_windows = _os_name.startswith("win32")
_is_x86 = _processor_arch.startswith("x86") or _processor_arch.startswith("amd")
_lib_name = "aria_sdk"
_lib_relative_path = ["shared"]

if not _is_windows:
    raise NotImplementedError(f"Aria SDK not supported on {_platform}")

# define platform
_lib_relative_path.append("windows")
_lib_name = _lib_name + ".dll"
# Determine architecture
if _is_x86 and _is_64_bits:
    _lib_relative_path.append("x64")
elif _is_x86 and not _is_64_bits:
    _lib_relative_path.append("x86")

# Find shared library in package
resource_package = __name__
resource_path = '/'.join(_lib_relative_path)

_libdir = pkg_resources.resource_filename(resource_package, resource_path)
_libpath = os.path.join(_libdir, _lib_name)
if not(os.path.exists(_libpath)): raise NotImplementedError(f"Aria SDK not supported on {_platform}")

from pythonnet import load
load("netfx")

import clr

path = os.path.join(_libpath)
clr.AddReference(path)

import aria_sdk
from aria_sdk import AriaIO, Instrument, Error, StepList, Monitoring, FlowControl, Configuration, Enums, Procedures, Step, Switches
from aria_sdk.Enums import ErrorSeverity, FlowRatePreset, SignalType, CalibrationState, FlowUnitType, StepParameter, StepType, SwitchType
from .sequence import Sequence

__version__ = "1.2.0"