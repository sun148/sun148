<html>
<head>
<meta http-equiv="refresh" content="3">
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.0/dist/css/bootstrap.min.css" 
rel="stylesheet" integrity="sha384-gH2yIJqKdNHPEq0n4Mqa/HGKIhSkIHeL5AyhkYV8i59U5AR6csBvApHHNl/vI1Bx" 
crossorigin="anonymous">

</head> 
<body>
	<div class="container mt-5 text-center">
  		<!-- Content here -->
		<h1>Monitor & Data log of Temperature Humidity @ ZONE Font of DATA CENTRE</h1>
		<br>
  		<?php
			date_default_timezone_set('Asia/Bangkok');
			$servername = "db";
			$username = "root";
			$password = "MYSQL_ROOT_PASSWORD";
			$dbname = "tutor";

			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) {
				die("Connection failed: " . $conn->connect_error);
			} 

			$sql = "SELECT * FROM esp8266 ORDER by id DESC LIMIT 25";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) {
				// output data of each row
				echo '<table class="table table-striped">
						<thead>
							<tr>
								<th class="text-success">ID</th>
								<th class="text-warning">Temperature</th>
								<th class="text-success">Humidity</th>
								<th class="text-info">&nbsp &nbsp &nbsp DATE-TIME</th>
							</tr>
						</thead>';
				while($row = $result->fetch_assoc()) {
					echo "<tr>";
					echo '<td class="text-success">'."&nbsp".$row['id']."</td>";
					echo '<td class="text-danger">'."&nbsp"."&nbsp"."&nbsp"."&nbsp"."&nbsp".$row['temp']." °C"."</td>";
					echo '<td class="text-success">'."&nbsp"."&nbsp"."&nbsp"."&nbsp".$row['HUM']." %"."</td>";
					echo '<td class="text-primary">'.$row['day']."</td>";
					echo "</tr>";
				}
				echo "</table>";
			} else {
				echo "0 results";
			}
			$conn->close();
		?>
	</div>

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.0/dist/js/bootstrap.bundle.min.js" 
integrity="sha384-A3rJD856KowSb7dwlZdYEkO39Gagi7vIsF0jrRAoQmDKKtQBHUuLZ9AsSv4jD4Xa" 
crossorigin="anonymous"></script>
</body>
</html>