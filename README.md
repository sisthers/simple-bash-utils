# simple-bash-utils
Implementation of basic Bash utilities: cat and grep. My first project made during my education in School 21.
Tests were not fully written by me. Works correctly on Ubuntu 22.04.

## Usage
### Download
```
git clone https://github.com/sisthers/simple-bash-utils.git
```
### Build
```
make s21_cat
make s21_grep
```
or
```
make all
```
### Run tests
```
make test_cat
make test_grep
```
or
```
make test
```
### Description
You can use it as original cat and grep commands, just replace ```cat``` or ```grep``` with ```./s21_cat``` or ```./s21_grep```.

### Cat options description
| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  |

### Grep options description
| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |
| 7 | -h | Output matching lines without preceding them by file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file. |
| 10 | -o | Output the matched parts of a matching line. |
