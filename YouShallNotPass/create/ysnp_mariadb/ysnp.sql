CREATE DATABASE IF NOT EXISTS `userdb`;
USE `userdb`;


CREATE TABLE IF NOT EXISTS `user` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `login` varchar(50) DEFAULT NULL,
  `password` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
);


DELETE FROM `user`;
INSERT INTO `user` (`id`, `login`, `password`) 
VALUES (1, 'Gandalf', 'SecretPa55word@');
