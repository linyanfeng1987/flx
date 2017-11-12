

  
CREATE TABLE `core`.`processtask` (
  `taskId` VARCHAR(45) NOT NULL,
  `rateName` VARCHAR(20) NULL,
  `rateType` INT NULL,
  `startTime` INT NULL,
  `endTime` INT NULL,
  `processName` VARCHAR(20) NULL,
  `paramter` VARCHAR(100) NULL,
  `status` INT NULL,
  PRIMARY KEY (`taskId`));
