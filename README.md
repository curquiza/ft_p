# ft_p

School project.

FTP client and server based on [RFC959](https://tools.ietf.org/html/rfc959) and [RFC2428](https://tools.ietf.org/html/rfc2428) (IPv6 extension).

## Compilation
```bash
$> make
```
## Server

```bash
$> cd ftp_server
$> ./server <port>
```

#### Options
- `-d`: debug mode (recommended)
- `-6`: handles IPv6

#### Commands
| name 	| definition 	| usage 	| 
|------	|------------	|---------	|
|`LIST`|ls-like command|`LIST [file/folder]`|
|`CWD`|change the current working directory|`CWD <folder>`|
|`PWD`|display the current working directory|`PWD`|
|`RETR`|get a file from the server|`RETR <file>`|
|`STOR`|put a file into the server|`STOR <file>`|
|`PORT`|data connection in active mode (IPv4 only)|`PORT <addr>,<port>`|
|`EPRT`|data connection in active mode (handles IPv6)|`EPRT \|<type>\|<addr>\|<port>\|`|
|`PASV`|data connection in passive mode (IPv4 only)|`PASV`|
|`EPSV`|data connection in passive mode (handles IPv6)|`EPSV`|

## Client

```bash
$> cd ftp_client
$> ./client <server_addr> <port>
```

#### Options
- `-6`: IPv6
- `-a`: force active mode

#### Commands
| usage|definition| 
|------|----------|
|`help`|Display all commands|
|`cd <path>`|Change the current working directory on the server|
|`pwd`|Get the current working directory on the server|
|`ls [path]`|Execute ls command|
|`put <filename>`|Upload the file on the server|
|`get <filename> [new_filename]`|Downlaod the file on the server|
|`mode`|Display the current mode (active/passive)|
|`pass`|On/off the passive mode|
|`quit`|Close the connection and exit the client|
