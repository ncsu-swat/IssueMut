# Fuzz4All

This folder contains crashes we find using Fuzz4All [1].

```shell
- Fuzz4All
  - crashes # contains all Fuzz4All crashes we found
    - crash.c # the generated C file cause compiler to crash
    - log.txt # the crash traces
  - inputs # contains logs Fuzz4All generated (compressed because the git limitation) 
    - logs.7z # contains logs, file generation logs, and compiler validation logs
```

### References
1. Chunqiu Steven Xia, Matteo Paltenghi, Jia Le Tian, Michael Pradel, and Lingming Zhang. 2024. Fuzz4All: Universal Fuzzing with Large Language Models. In Proceedings of the IEEE/ACM 46th International Conference on Software Engineering (ICSE '24). Association for Computing Machinery, New York, NY, USA, Article 126, 1–13. DOI: [Link](https://doi.org/10.1145/3597503.3639121)