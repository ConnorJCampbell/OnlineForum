<?php
	$cmd = './translator index.wpml';
	exec($cmd, $output, $status);

	if($status) {
		echo "exec() failed";
	}
	else {
		foreach ($output as $line) {
			echo($line);
		}
	}
?>