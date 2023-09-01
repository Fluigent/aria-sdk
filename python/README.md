# Aria SDK middleware

This groups a package structure that allows for a quick installation with `pip` and a basic example script written in Python (3+), demonstrating the basic usage of the Fluigent Aria SDK.

## Setup and test
- Place the SDK DLLs in a folder called `dlls/` in the repository root, with the paths `win/x86/aria_sdk.dll` and `win/x64/aria_sdk.dll`
- Go to the package directory: `cd package/`
- Run `python deploy.py`
- Install the SDK with `pip install dist/aria_sdk-X.X.X.zip`
- Then test with the example script: `cd ../ && python example/aria-sdk-example.py`

## Distribution
- Once generated, copy `package/dist/aria_sdk-X.X.X.zip` file and the `example/` folder to the release archive.
