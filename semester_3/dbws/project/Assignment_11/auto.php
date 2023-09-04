<?php
require_once('connection.php');

function get_name($connect , $term){
        $query = "SELECT * FROM person WHERE full_name LIKE '%".$term."%' ORDER BY id ASC";
        $result = mysqli_query($connect, $query);
        $data = mysqli_fetch_all($result,MYSQLI_ASSOC);
        return $data;
}

if (isset($_GET['term'])) {
        $getname = get_name($conn, $_GET['term']);
        $nameList = array();
        foreach($getname as $name){
                $nameList[] = $name['full_name'];
        }
        echo json_encode($nameList);
}
?>