<?php

	$user = $_POST['Username'];
	echo("Username: ". $user . "<BR>");
	$currentStream = $_POST['stream'];
	echo("Stream: ". $currentStream . "<BR>");
	$postCount = $_POST['Counter'];

	$cmd = './translator view_2.wpml';
	exec($cmd, $output, $status);


	
	if(isset($_POST['next'])) {
		
		$postCount++;
		if(strcmp($currentStream, "all") != 0) {
			if($postCount >= 0) {
				$postCount = 0;
			}
		}

		$cmd = 'python3 ./view.py ' . escapeshellarg($user) . ' ' . escapeshellarg($currentStream) . ' a ' . $postCount;
		exec($cmd, $result, $status2);
		foreach ($result as $print) {
			if(strcmp($currentStream, "all") == 0) {
				if(strstr($print, "-----You have reached the Final Post-----<BR>") != NULL) {
					$postCount--;
				}
			}
		}

		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($output as $line) {
				if(strstr($line, "UsernameToReplace") != NULL) {
					echo str_replace("UsernameToReplace", $user, $line);
				}
				else if(strstr($line, "COUNTTOADD") != NULL) {
					echo str_replace("COUNTTOADD", $postCount, $line);
				}
				else if(strstr($line, "STREAMTOADD") != NULL) {
					echo str_replace("STREAMTOADD", $currentStream, $line);
				}
				else
					echo($line);
			}
		}

		
		if($status2) {
			echo "exec() failed";
		}
		else {
			foreach ($result as $print)
				echo($print);
		}

	}
	else if(isset($_POST['previous'])) {
		
		$postCount--;

		$cmd = 'python3 ./view.py ' . escapeshellarg($user) . ' ' . escapeshellarg($currentStream) . ' s ' . $postCount;
		exec($cmd, $result, $status2);
		foreach ($result as $print) {
			if(strstr($print, "---You have reached the first post---<BR>") != NULL) {
				$postCount++;
			}
		}

		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($output as $line) {
				if(strstr($line, "UsernameToReplace") != NULL) {
					echo str_replace("UsernameToReplace", $user, $line);
				}
				else if(strstr($line, "COUNTTOADD") != NULL) {
					echo str_replace("COUNTTOADD", $postCount, $line);
				}
				else if(strstr($line, "STREAMTOADD") != NULL) {
					echo str_replace("STREAMTOADD", $currentStream, $line);
				}
				else
					echo($line);
			}
		}

		if($status2) {
			echo "exec() failed";
		}
		else {
			foreach ($result as $print)
				echo($print);
		}
	}
	else if(isset($_POST['Mark_All'])) {
		
		$postCount = 0;
		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($output as $line) {
				if(strstr($line, "UsernameToReplace") != NULL) {
					echo str_replace("UsernameToReplace", $user, $line);
				}
				else if(strstr($line, "COUNTTOADD") != NULL) {
					echo str_replace("COUNTTOADD", $postCount, $line);
				}
				else if(strstr($line, "STREAMTOADD") != NULL) {
					echo str_replace("STREAMTOADD", $currentStream, $line);
				}
				else
					echo($line);
			}
		}

		$cmd = 'python3 ./view.py ' . escapeshellarg($user) . ' ' . escapeshellarg($currentStream) . ' m ' . $postCount;
		exec($cmd, $result, $status);
		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($result as $print)
				echo($print);
		}
	}

	else if(isset($_POST['Refresh'])) {
		
		$postCount = 0;
		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($output as $line) {
				if(strstr($line, "UsernameToReplace") != NULL) {
					echo str_replace("UsernameToReplace", $user, $line);
				}
				else if(strstr($line, "COUNTTOADD") != NULL) {
					echo str_replace("COUNTTOADD", $postCount, $line);
				}
				else if(strstr($line, "STREAMTOADD") != NULL) {
					echo str_replace("STREAMTOADD", $currentStream, $line);
				}
				else
					echo($line);
			}
		}

		$cmd = 'python3 ./view.py ' . escapeshellarg($user) . ' ' . escapeshellarg($currentStream) . ' v ' . $postCount;
		exec($cmd, $result, $status);
		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($result as $print)
				echo($print);
		}
	}

	else if(isset($_POST['Order'])) {
		
		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($output as $line) {
				if(strstr($line, "UsernameToReplace") != NULL) {
					echo str_replace("UsernameToReplace", $user, $line);
				}
				else if(strstr($line, "COUNTTOADD") != NULL) {
					echo str_replace("COUNTTOADD", $postCount, $line);
				}
				else if(strstr($line, "STREAMTOADD") != NULL) {
					echo str_replace("STREAMTOADD", $currentStream, $line);
				}
				else
					echo($line);
			}
		}

		echo "The order function is incomplete.";
	}

	else {
		$postCount = 0;
		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($output as $line) {
				if(strstr($line, "UsernameToReplace") != NULL) {
					echo str_replace("UsernameToReplace", $user, $line);
				}
				else if(strstr($line, "COUNTTOADD") != NULL) {
					echo str_replace("COUNTTOADD", $postCount, $line);
				}
				else if(strstr($line, "STREAMTOADD") != NULL) {
					echo str_replace("STREAMTOADD", $currentStream, $line);
				}
				else
					echo($line);
			}
		}
		$cmd = 'python3 ./view.py ' . escapeshellarg($user) . ' ' . escapeshellarg($currentStream) . ' v '. $postCount;
		exec($cmd, $result, $status);
		if($status) {
			echo "exec() failed";
		}
		else {
			foreach ($result as $print)
				echo($print);
		}
	}

?>