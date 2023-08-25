# Aria SDK middleware

This groups a package structure that allows for a quick installation with `pip` and a basic example script written in Python (3+), demonstrating the basic usage of the Fluigent Aria SDK.

## Setup and test
- Place the SDK DLLs in a folder called `dlls/` in the repository root, with the paths `win/x86/*.dll` and `win/x64/*.dll`
- Go to the package directory: `cd package/`
- Run `python deploy.py`
- Install the SDK with `pip install dist/2sw/aria_sdk-1.2.0.zip` or `pip install dist/Msw/aria_sdk-1.2.0.zip`
- Then test with the example script: `cd ../ && python example/aria-sdk-example.py`

## Distribution
- Once generated, copy `package/dist/2sw/aria_sdk-1.2.0.zip` and/or `package/dist/Msw/aria_sdk-1.2.0.zip` file and the `example/` folder to the release archive.
