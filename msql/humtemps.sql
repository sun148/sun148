-- Create DataBase Name : tutor <=====

-- Delete Table If Exists
DROP TABLE IF EXISTS esp8266 ;

-- Create Table
CREATE TABLE `esp8266` (
`id` int(11) NOT NULL,
`temp` int(11) NOT NULL,
`day` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;