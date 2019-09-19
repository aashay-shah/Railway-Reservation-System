-- phpMyAdmin SQL Dump
-- version 4.6.5.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Sep 19, 2019 at 08:29 PM
-- Server version: 10.1.21-MariaDB
-- PHP Version: 7.1.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `railway`
--

-- --------------------------------------------------------

--
-- Table structure for table `login`
--

CREATE TABLE `login` (
  `USER_ID` int(11) NOT NULL,
  `USER_NAME` varchar(30) DEFAULT NULL,
  `PASSWORD` varchar(30) DEFAULT NULL,
  `ROLE` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `login`
--

INSERT INTO `login` (`USER_ID`, `USER_NAME`, `PASSWORD`, `ROLE`) VALUES
(1, 'aashay.shah', 'aashayshah', 'user'),
(2, 'u.savla', 'umangsavla', 'user'),
(3, 'prithvi.shah', 'prithvishah', 'user'),
(4, 'admin', 'admin', 'admin');

-- --------------------------------------------------------

--
-- Table structure for table `passenger`
--

CREATE TABLE `passenger` (
  `P_ID` int(11) NOT NULL,
  `P_NAME` varchar(30) DEFAULT NULL,
  `AGE` int(5) DEFAULT NULL,
  `TRAIN_ID` int(11) DEFAULT NULL,
  `CLASS` varchar(20) DEFAULT NULL,
  `COST` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `passenger`
--

INSERT INTO `passenger` (`P_ID`, `P_NAME`, `AGE`, `TRAIN_ID`, `CLASS`, `COST`) VALUES
(2, 'Saiyam', 20, 11002, 'Second', 750);

-- --------------------------------------------------------

--
-- Table structure for table `train`
--

CREATE TABLE `train` (
  `PNR` int(11) NOT NULL,
  `T_NAME` varchar(30) DEFAULT NULL,
  `SRC` varchar(30) DEFAULT NULL,
  `DEST` varchar(30) DEFAULT NULL,
  `FC_T` int(11) DEFAULT NULL,
  `FC_C` int(11) DEFAULT NULL,
  `SC_T` int(11) DEFAULT NULL,
  `SC_C` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `train`
--

INSERT INTO `train` (`PNR`, `T_NAME`, `SRC`, `DEST`, `FC_T`, `FC_C`, `SC_T`, `SC_C`) VALUES
(11001, 'Shatabdi Express', 'CST', 'Amhedabad', 60, 500, 360, 200),
(11002, 'Gareebrath Express', 'Delhi', 'Dadar', 120, 1500, 299, 750);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `login`
--
ALTER TABLE `login`
  ADD PRIMARY KEY (`USER_ID`),
  ADD UNIQUE KEY `USER_NAME` (`USER_NAME`);

--
-- Indexes for table `passenger`
--
ALTER TABLE `passenger`
  ADD PRIMARY KEY (`P_ID`);

--
-- Indexes for table `train`
--
ALTER TABLE `train`
  ADD PRIMARY KEY (`PNR`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `login`
--
ALTER TABLE `login`
  MODIFY `USER_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT for table `passenger`
--
ALTER TABLE `passenger`
  MODIFY `P_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
