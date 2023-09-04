<?php
$_SERVER = "localhost";
$myusername = "group30";
$mypassword = "apachewhich";
$dbName = "group30";

// create connection
$conn = mysqli_connect($serverName, $userName, $password, $dbName);
if (mysqli_connect_errno()) {
    echo "Failed to connect to DB!";
    exit();
}
