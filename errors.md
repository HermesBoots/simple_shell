| Command            | `errno =` (Macro) | `perror(NULL)` Output             | `sh` Error Message                                   |
| ------------------ | ----------------- | --------------------------------- | ---------------------------------------------------- |
| ./textfile         | EACCES            | Permission denied                 | sh: 1: ./textfile: Permission denied                 |
| ./corruptexe       | EIO               | Input/output error                | sh: 2: ./corruptexe: Input/output error              |
| ./textfile/exefile | ENOTDIR           | Not a directory                   | sh: 3: ./textfile/exefile: not found                 |
| ./looplink         | ELOOP             | Too many levels of symbolic links | sh: 4: ./looplink: Too many levels of symbolic links |
| ./AAAAAAAAAAAAAAA… | ENAMETOOLONG      | File name too long                | sh: 5: ./AAAAAAAAAAAAAAAAAAAAAA…: File name too long |
| ./notafile         | ENOENT            | No such file or directory         | sh: 6: ./notafile: not found                         |
