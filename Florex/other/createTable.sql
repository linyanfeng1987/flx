 
drop table `core`.`processtask`;
CREATE TABLE `core`.`processtask` (
  `taskId` VARCHAR(45) NOT NULL,
  `processTypeName` VARCHAR(20) NOT NULL,
  `rate` VARCHAR(20) NULL,
  `rateType` VARCHAR(20) NULL,
  `startTime` INT NULL,
  `endTime` INT NULL,
  `paramter` VARCHAR(100) NULL,
  `status` INT default 0,
  PRIMARY KEY (`taskId`));

drop table `core`.`processstatus`;
CREATE TABLE `core`.`processstatus` (
  `processName` VARCHAR(30) NOT NULL,
  `processStatus` INT NOT NULL DEFAULT 0,
  `buildTaskLastTime` INT NOT NULL DEFAULT 0,
  `completeTaskLastTime` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`processName`));
