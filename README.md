# PluginSample
Sample of a plugin system using .so files

This is a sample of using dynamic libraries as plugins.

The sample defines a small API to work with the library files.

There are two sample plugins, and a main to show how the system works.

To compile the example use this command:

```bash
  g++ -I . main.cpp -o main -ldl
```

To compile the plugins the command is as follows:

```bash
  g++ -shared -I . -o plugins/TrimedTextPlugin.so -fPIC plugins/TrimedTextPlugin.cpp
  g++ -shared -I . -o plugins/RawTextPlugin.so -fPIC plugins/RawTextPlugin.cpp
```
