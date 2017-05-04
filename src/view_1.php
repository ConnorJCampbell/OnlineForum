<?php

	$user = $_POST['Username'];
	echo("Username: ". $user);

	$cmd = './translator view_1.wpml';
	exec($cmd, $output, $status);
	if($status) {
		echo "exec() failed";
	}
	else {
		foreach ($output as $line) {
			if(strstr($line, "UsernameToReplace") != NULL) {
				echo str_replace("UsernameToReplace", $user, $line);
			}
			else if(strstr($line, "COUNTTOADD") != NULL) {
				echo str_replace("COUNTTOADD", "0", $line);
			}
			else {
				echo($line);
				if(strstr($line, "You have access to the following streams:") != NULL) {
					$cmd = 'python3 ./produceList.py ' . escapeshellarg($user);
					exec($cmd, $result, $status);
					echo(" ");
					if($status)
						echo "exec() failed";

					else {
						foreach ($result as $print)
							echo($print);	
					}
				}
			}
		}
	}
?>