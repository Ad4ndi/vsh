section .data

global prompt
global path

path   db "/usr/local/bin:/bin:/usr/bin:/sbin:/usr/local/sbin", 0
prompt db "\c(2)\w $ \c(7)", 0