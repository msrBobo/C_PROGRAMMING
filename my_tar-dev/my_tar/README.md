# Welcome to My Tar
***
 
## Task
my_tar is a command to manipulate tape archive. The first option to tar is a mode indicator from the following list:

In -c, -r, or -u mode, each specified file or directory is added to
the archive in the order specified on the command line. By default, the contents of each directory are also archived.

## Description
Feb 6 - https://asciinema.org/a/557917
Feb 7 - https://asciinema.org/a/558145
Feb 8 - https://asciinema.org/a/558409
Feb 9 - https://asciinema.org/a/558730
Feb 10 - https://asciinema.org/a/559006
Feb 11 - https://asciinema.org/a/559505
Feb 13 - https://asciinema.org/a/559629

## Installation
download, unpack if it is packed, and run make

## Usage
run the following ./my_tar [options] [file]

-c Create a new archive containing the specified items.
-r Like -c, but new entries are appended to the archive. The -f option is required.
-t List archive contents to stdout.
-u Like -r, but new entries are added only if they have a modification date newer than the corresponding entry in the archive. The -f option is required.
-x Extract to disk from the archive. If a file with the same name appears more than once in the archive, each copy will be extracted, with later copies overwriting (replacing) earlier copies.
-f file Read the archive from or write the archive to the specified
file.

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
