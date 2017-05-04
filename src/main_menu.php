<?php
	if(isset($_POST['Username'])) {
		if(trim($_POST['Username']) == '') {
			$user = "GUEST";
		}
		else	
			$user = $_POST['Username'];
	}
	
	// if(file_exists("current_user")) {
	// 	$fp = fopen("current_user", "r");
	// 	$user = fgets($fp);
	// 	fclose($fp);
	// }
	// else {
	// 	$user = "GUEST";
	// }
	echo "Username: " . $user;

	$cmd = './translator main_menu.wpml';
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


	if(isset($_POST['choice'])) {
		if(isset($_POST['authorStream'])) {
	
			switch($_POST['choice']) {
				case 'Add':
					exec('./addauthor ' . escapeshellarg($_POST['authorStream']) . ' ' . escapeshellarg($user), $result);
					foreach ($result as $line) {
						echo($line);
					}
					break;
				case 'Remove':
					exec('./addauthor -r ' . escapeshellarg($_POST['authorStream']) . ' '. escapeshellarg($user), $result);
					foreach ($result as $line) {
						echo($line);
					}
					break;
			}
		}
	}
?>