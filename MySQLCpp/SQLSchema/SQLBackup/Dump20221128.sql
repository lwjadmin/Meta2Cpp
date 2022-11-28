CREATE DATABASE  IF NOT EXISTS `guestbook` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `guestbook`;
-- MySQL dump 10.13  Distrib 8.0.31, for Win64 (x86_64)
--
-- Host: localhost    Database: guestbook
-- ------------------------------------------------------
-- Server version	8.0.31

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `board`
--

DROP TABLE IF EXISTS `board`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `board` (
  `ID_BOARD` bigint NOT NULL AUTO_INCREMENT,
  `TITLE` varchar(300) NOT NULL,
  `CONTENT` varchar(4000) DEFAULT NULL,
  `REGUSER_ID` bigint DEFAULT NULL,
  `REGDATE` datetime NOT NULL DEFAULT (now()),
  `VIEWCNT` int NOT NULL DEFAULT '0',
  `LIKECNT` int NOT NULL DEFAULT '0',
  `DISLIKECNT` int NOT NULL DEFAULT '0',
  `THUMBNAIL_FILE_ID` bigint DEFAULT NULL,
  `DEL_YN` char(1) NOT NULL DEFAULT 'N',
  PRIMARY KEY (`ID_BOARD`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `board`
--

LOCK TABLES `board` WRITE;
/*!40000 ALTER TABLE `board` DISABLE KEYS */;
INSERT INTO `board` VALUES (1,'HELLO','NICE TO MEET YOU!',NULL,'2022-11-28 14:04:37',0,0,0,NULL,'N');
/*!40000 ALTER TABLE `board` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sheet1`
--

DROP TABLE IF EXISTS `sheet1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `sheet1` (
  `IDX` int NOT NULL AUTO_INCREMENT,
  `NAME` char(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `CONTENT` char(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `COUNT` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`IDX`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sheet1`
--

LOCK TABLES `sheet1` WRITE;
/*!40000 ALTER TABLE `sheet1` DISABLE KEYS */;
INSERT INTO `sheet1` VALUES (2,'A2','HELLO2',0),(3,'A3','HELLO3',0),(4,'A4','HELLO4',0),(5,'A5','HELLO5',0),(6,'A1','HELLO1',0),(7,'A1','HELLO1',0),(8,'A2','HELLO2',0),(9,'A3','HELLO3',0),(10,'A4','HELLO4',0),(11,'A5','HELLO5',0);
/*!40000 ALTER TABLE `sheet1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'guestbook'
--

--
-- Dumping routines for database 'guestbook'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-11-28 15:01:47
