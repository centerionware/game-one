<style type="text/css">
td {
	height: 30px;
	width: 30px;
	font-size: 15px;
	font-weight: bold;
	border: 1px solid #000;
	text-align: center;
}
table {
	border-collapse: collapse;
}
.selected0 {
	background-color: yellow;
}
.selected1 {
	background-color: green;
}
</style>
<?php

function getnumerics($width,$height,$pos,$distance) {
	$temp = str_replace(0,10,$pos % 10);

echo $temp;
	$arr[$pos] = 0;
	$arr[$pos+($width*($distance/2))] = 0;
	$arr[$pos-$width] = 0;

//top row
	if ($pos+($width*$distance) > $temp) {
		if ($temp > 2) $arr[($pos-($width*($distance)+($distance)))] = 1;
		if ($temp > 1) $arr[($pos-($width*($distance)+($distance/2)))] = 1;
		$arr[(($pos-($width*$distance)))] = 1;
		if ($temp+($distance/2) <= $width) $arr[($pos-($width*($distance)-($distance/2)))] = 1;
		if (($temp+($distance/2)) < $width) $arr[($pos-($width*($distance)-($distance)))] = 1;
	}

//bottom row.
	if ($pos+($width*$distance) > $temp) {
		if (($temp+($distance/2)) > 3) $arr[($pos+($width*($distance)-($distance)))] = 1;
		if (($temp+($distance/2)) >  $distance) $arr[($pos+($width*($distance)-($distance/2)))] = 1;
		$arr[($pos+($width*$distance))] = 1;
		if ($temp < $width) $arr[($pos+($width*($distance)+($distance/2)))] = 1;
		if ($temp+($distance/2) < $width) $arr[($pos+($width*($distance)+($distance)))] = 1;
		if (($temp+($distance/2)) > $distance) $arr[($pos+($width*($distance)-($distance/2)))] = 1;
	}
	if (($temp+($distance/2)) <= $width) {
		$arr[(($pos+$width) + $distance/2)] = 0;
		$arr[(($pos-$width) + $distance/2)] = 0;
		$arr[$pos+($distance/2)] = 0;
	}

//right row
	if ($temp+$distance <= $width) {
		$arr[(($pos+$width) + $distance)] = 1;
		$arr[(($pos-$width) + $distance)] = 1;
		$arr[$pos+($distance)] = 1;
	}
	if ($temp > 1) {
		$arr[(($pos+$width) - $distance/2)] = 0;
		$arr[(($pos-$width) - $distance/2)] = 0;
		$arr[$pos-($distance/2)] = 0;
	}
//left row
	if ($temp > 2) {
		$arr[(($pos+$width) - $distance)] = 1;
		$arr[(($pos-$width) - $distance)] = 1;
		$arr[$pos-($distance)] = 1;
	}
	return $arr;
}
$num = (!empty($_GET['num'])?$_GET['num']:1);

$arr = getnumerics(10,10,$num,2);
echo '<table><tr>';
for($i = 1; $i <= 100; $i++) {
	$out[] = '<td'.(isset($arr[$i])?' class="selected'.$arr[$i].'"':'') .'><a href="/test.php?num='.$i.'">'.$i.'</a></td>';
	if ($i % 10 === 0) $out[] = '</tr><tr>';
}
echo substr(implode('',$out),0,-4);
echo '</table>';