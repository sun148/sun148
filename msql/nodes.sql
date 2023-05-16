-- Delete Table If Exists
DROP TABLE IF EXISTS nodes ;

-- Create Table
CREATE TABLE nodes  (
	id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
	nodeid VARCHAR(255) NOT NULL,
	color VARCHAR(255) NOT NULL,
	button VARCHAR(255) NOT NULL,
	created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
	updated_at DATETIME
);

-- Insert users data
INSERT INTO nodes (
	nodeid,
	color,
	button
) VALUES (
	'LOPBURI-Mueang-demo1',
	'RED',
	'Start button'
);

-- password = Haha.555