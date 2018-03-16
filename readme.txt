This program is supposed to index files within either a directory or within the current directory and create a file which prints the inverted index of each file found in that directory and the files witin the directory's directories if any exist.

EX: ./Asst2 "Indexes" "DD"
OUTPUT: "Are you sure you want to delete this file? Enter y for yes, anything else for no."
INPUT: y
IN FILE Indexes IN CURRENT DIRECTORY:
<?xml version= "1.0" encoding="UTF-8"?>
<fileIndex>
        <word text ="deffinitely">
                <file name = "file1.txt">1</file>
                <file name = "file.txt">1</file>
        </word>
        <word text ="fie">
                <file name = "file.txt">1</file>
        </word>
        <word text ="for">
                <file name = "file.txt">1</file>
        </word>
        <word text ="fum">
                <file name = "file.txt">1</file>
        </word>
        <word text ="hahh">
                <file name = "file2.txt">1</file>
        </word>
        <word text ="yes">
                <file name = "file3.txt">1</file>
        </word>
</fileIndex>
