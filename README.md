# Fluigent Aria SDK

## Objective

Aria Software Development Kit (SDK) allows you to fully integrate Aria device in your application; it has been declined in several languages, namely C\# .NET, C++ and Python.

Its usage is supposed to provide, at a lower level, all functionalities available in its UI counterpart. 
As for the Aria UI software, the Aria SDK lies on the control of Aria via sequences (or protocols). 
Even if some remote control of the individual components is possible, the SDK really shines when it comes to schedule some long sequences of commands. 
Taking all possible parameters into account, Aria SDK is able to play a sequence of injection from multiple reservoirs and to multiple output channels while minimizing the consumption of chemical products (buffer, cell culture, etc.). 

## Releases

As of today, last version of the SDK is **v1.2** and can be downloaded from the [Release page](https://github.com/Fluigent/aria-sdk/releases/latest). 
It is provided as an archive file (.zip) and contains the 3 languages support files, as well as examples for each, and the necessary libraries.

## Requirements

Aria SDK is available for Windows **x32** and **x64** architectures and we ensure the full compatibility with **Windows 10 and more**.

## Middlewares

The Aria SDK is a C# library built for windows and written in C\#.
The SDK functions are detailed in the manual (**Aria_SDK.pdf**) and an example project is provided in the **csharp** folder.

It also supports two other major programming languages as additional packages : C++ and Python.
They are collectively referred to as Middleware. Each package has its own folder and within the folder a README file to help with the installation as well as an example to test it.
Please look at the manual for further details.

We **strongly recommend** using the Middleware if your programming language of choice is supported.
It is open source, so you can modify it to suit your needs. To do so, simply clone the current repository and make your changes. 
Compiled packages can be found in the archives hosted in the Release page.

Here are the package contents:

| **Language** | **Package** |
|--------------|-------------|
| C++          | **main.cpp** example script <br> **aria_sdk_example_cpp.sln** Visual Studio complete solution containing middleware and examples |
| C#           | **Program.cs** example script <br> **aria-sdk-example.sln** Visual Studio complete solution containing middleware and examples |
| Python       | **aria-sdk-example.py** example script |

## Support

For any question, please contact support@fluigent.com 