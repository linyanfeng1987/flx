drop table `florex`.`currency_pair_eurusd`;
CREATE TABLE `florex`.`currency_pair_eurusd` (
  `startTime` INT NOT NULL,
  `price` FLOAT NOT NULL,
  `volume` FLOAT NOT NULL,
  `timeFormat` VARCHAR(45) NULL,
  PRIMARY KEY (`startTime`));

drop table `florex`.`currency_pair_usdjpy`;
CREATE TABLE `florex`.`currency_pair_udsjpy` (
  `startTime` INT NOT NULL,
  `price` FLOAT NOT NULL,
  `volume` FLOAT NOT NULL,
  `timeFormat` VARCHAR(45) NULL,
  PRIMARY KEY (`startTime`));

drop table `florex`.`currency_pair_xauusd`;
CREATE TABLE `florex`.`currency_pair_xauusd` (
  `startTime` INT NOT NULL,
  `price` FLOAT NOT NULL,
  `volume` FLOAT NOT NULL,
  `timeFormat` VARCHAR(45) NULL,
  PRIMARY KEY (`startTime`));
  
drop table `florex`.`currency_pair_gbpusd`;
CREATE TABLE `florex`.`currency_pair_gbpusd` (
  `startTime` INT NOT NULL,
  `price` FLOAT NOT NULL,
  `volume` FLOAT NOT NULL,
  `timeFormat` VARCHAR(45) NULL,
  PRIMARY KEY (`startTime`));
  
drop table `florex`.`currency_pair_audusd`;
CREATE TABLE `florex`.`currency_pair_audusd` (
  `startTime` INT NOT NULL,
  `price` FLOAT NOT NULL,
  `volume` FLOAT NOT NULL,
  `timeFormat` VARCHAR(45) NULL,
  PRIMARY KEY (`startTime`));
  


  
