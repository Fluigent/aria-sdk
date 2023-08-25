from setuptools import setup, find_packages

setup(name="aria_sdk",
      version="1.2.0",
      description="SDK for Aria Instrument",
      url="https://www.fluigent.com",
      author="Fluigent",
      author_email="support@fluigent.com",
      license="Proprietary",
      packages=find_packages(exclude=("tests",)),
      namespace_packages=["Aria"],
      package_data={"Aria.SDK": ["shared/windows/*/*.dll"]},
      install_requires=[
          'pythonnet',
      ],
      zip_safe=False)
