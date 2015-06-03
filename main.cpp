/*
 The MIT License (MIT)

 Copyright (c) 2015 Blackcatn13

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "src/pluginApi.h"
#include "src/BasePlugin.h"

int main(int argc, char **argv) {
  std::vector<std::string> PluginsNameList = std::vector<std::string>();
  std::vector<PluginInfo*> PluginsInfoList;
  std::vector<BasePlugin*> PluginsList;
  std::vector<void*> PluginsHandleList;
  // Get the plugins names from the PluginsList file
  std::ifstream PluginsFile("plugins/PluginsList.txt");
  if (PluginsFile.is_open()) {
    std::string line;
    while (getline(PluginsFile, line)) {
      PluginsNameList.push_back(line);
    }
    PluginsFile.close();
  }
  // Load all the plugins in order
  for (size_t i = 0; i < PluginsNameList.size(); ++i) {
    char *error;
    std::string fileName = "plugins/" + PluginsNameList[i] + ".so";
    void *handle = dlopen(fileName.c_str(), RTLD_LAZY);
    // If no handle is present, the plugin has not been load, show the error
    if (!handle) {
      std::cerr << "Cannot open plugin " << PluginsNameList[i] << std::endl;
      std::cerr << "More info: " << dlerror() << std::endl;
      continue;
    }
    PluginsHandleList.push_back(handle);
    // Clear any existing error
    dlerror();
    PluginInfo* info = reinterpret_cast<PluginInfo*>(dlsym(handle,
                                                           "information"));
    if ((error = dlerror()) != NULL) {
      std::cerr << "Error loading plugin " << PluginsNameList[i]
                << " information" << std::endl;
      std::cerr << "More info: " << error << std::endl;
    }
    dlerror();
    PluginsInfoList.push_back(info);

    BasePlugin* plugin = reinterpret_cast<BasePlugin*>(info->getPlugin());
    PluginsList.push_back(plugin);
  }

  // Show the loaded plugins info
  for (size_t i = 0; i < PluginsInfoList.size(); ++i) {
    PluginInfo* info = PluginsInfoList[i];
    std::cout << "Plugin info" << std::endl;
    std::cout << "\tAPI version: " << info->apiVersion << std::endl;
    std::cout << "\tPlugin source file: " << info->fileName << std::endl;
    std::cout << "\tPlugin class name: " << info->className << std::endl;
    std::cout << "\tPlugin name: " << info->pluginName << std::endl;
    std::cout << "\tPlugin version: " << info->pluginVersion << std::endl;
    std::cout << "\tPlugin brief description: " << info->pluginDescription
              << std::endl;
  }

  // Execute the function of the plugins
  for (size_t i = 0; i < PluginsList.size(); ++i) {
    PluginsList[i]->textCommand("This is a test of the plugin system", 14);
  }

  // Close the dynamic library bindings
  for (size_t i = 0; i < PluginsHandleList.size(); ++i) {
    dlclose(PluginsHandleList[i]);
  }
}
