#Funcții ajutătoare pentru examenul de soc

USART 				- implementat
USART formatting 	- implementat
CRC16/CRC32			- implementat, testat pe simulator


Pentru verificare CRC, trebuie scos opțiunea de "fill unused interrupt vectors with RETI" și la Linker la checksum trebuie selectat polinomul corespunzător și mărimea checksum-ului aferentă.