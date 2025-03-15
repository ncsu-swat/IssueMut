# Fuzz4All

This folder contains crashes we find using Fuzz4All.

```shell
- Fuzz4All
  - crashes # contains all Fuzz4All crashes we found
    - crash.c # the generated C file cause compiler to crash
    - log.txt # the crash traces
  - inputs # contains logs Fuzz4All generated (compressed because the git limitation) 
    - logs.7z # contains logs, file generation logs, and compiler validation logs
```
