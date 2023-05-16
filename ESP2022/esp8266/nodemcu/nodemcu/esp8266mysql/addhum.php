<?php
$hum = $_GET['hum'];

$servername = "localhost";
$username = "root";
$password = "TDB@ITSupp0rt";
$dbname = "tutor";

// Create connection
$conn = new mysqli($servername, $username,$password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
$val = $_GET['hum'];
$sql = "INSERT INTO esp8266(hum) VALUES ($val);";

if ($conn->query($sql) === TRUE) {
    echo "save OK";
} else {
    echo "Error:" . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
