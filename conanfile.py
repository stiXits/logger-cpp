from conans import ConanFile, CMake
from os import path, getcwd, environ
import os

class LoggerConan(ConanFile):
   name = "logger"
   version = "0.1.0"
   author = "xqp"
   settings = "os", "compiler", "build_type", "arch"
   generators = "cmake_find_package"
   root = "%s-%s" % (name, version)

   def source(self):
      self.run("git clone https://github.com/xqp/logger-cpp.git")
      os.rename(self.name, self.root)

   def build(self):
      self.run("cd %s" % (self.root))
      cmake = CMake(self)
      cmake.definitions["CMAKE_INSTALL_PREFIX"] = "."
      cmake.configure(source_dir=self.root)
      cmake.build()
      cmake.install()

   def package(self):
      self.copy("license.txt",  dst=".", src=self.root)
      self.copy(pattern="*", dst="include", src=path.join(self.root, "include"))
      self.copy(pattern="*.lib", dst="lib", src="lib", keep_path=False)
      self.copy(pattern="*.a", dst="lib", src="lib", keep_path=False)

   def package_info(self):
      self.cpp_info.libs.append("logger")

