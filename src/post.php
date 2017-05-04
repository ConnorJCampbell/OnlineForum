<?php
	$user = $_POST['Username'];
	echo("Username: ". $user);

	$cmd = './translator post.wpml';
	exec($cmd, $output, $status);

	if($status) {
		echo "exec() failed";
	}
	else {
		foreach ($output as $line) {
			if(strstr($line, "UsernameToReplace") != NULL) {
				echo str_replace("UsernameToReplace", $user, $line);
			}
			else
				echo($line);
		}
	}

	if(isset($_POST['stream'])) {
		if(trim($_POST['stream']) == '') {
			echo("Please enter at least one stream");
		}
		else if(strpos($_POST['stream'], ' ') !== false) {
			echo "Do not enter any spaces in the stream";
		}
		else if(isset($_POST['text'])){
			$message = $_POST['text'] . "\n";
			exec('./post ' . escapeshellarg($user) . ' ' . $_POST['stream'] . ' ' . escapeshellarg($message), $result, $status);
			if($status) {
				echo "exec() failed";
			}
			else {
				foreach ($result as $print) {
					echo($print);
				}
			}	
		}
		else {
			echo "Please enter some text in the message box.";
		}
	}
?>