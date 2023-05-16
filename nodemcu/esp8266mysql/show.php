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
		<h1>Node MCU DATA Recorder</h1>
		<br>
  		<?php
			$servername = "db";
			$username = "root";
			$password = "MYSQL_ROOT_PASSWORD";
			$dbname = "node-db-y2023";

			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) {
				die("Connection failed: " . $conn->connect_error);
			} 

			$sql = "SELECT * FROM nodes ORDER by id DESC LIMIT 25";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) {
				// output data of each row
				echo '<table class="table table-striped">
						<thead>
							<tr>
								<th class="text-success">ID</th>
								<th class="text-warning">Color MCU read</th>
								<th class="text-success">Botton MCU read</th>
								<th class="text-info">&nbsp &nbsp &nbsp DATE-TIME</th>
							</tr>
						</thead>';
				while($row = $result->fetch_assoc()) {
					echo "<tr>";
					echo '<td class="text-success">'."&nbsp".$row['nodeid']."</td>";
					echo '<td class="text-danger">'."&nbsp"."&nbsp"."&nbsp"."&nbsp"."&nbsp".$row['color']." °C"."</td>";
					echo '<td class="text-success">'."&nbsp"."&nbsp"."&nbsp"."&nbsp".$row['button']." %"."</td>";
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