<?php include "./connection.php"; ?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width" , initial-scale="1.0">
    <title>PMS</title>
    <link rel="icon" href="../images/favicon.png">
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <div class="topbar">
        <a href="about.html">About</a>
        <a href="imprint.html">Imprint</a>
    </div>
    <div class="sidebar">
        <a href="index.html">
            <img src="../images/favicon.png" alt="logo">
        </a>
        <a href="../index.html">Home</a>
        <a href="../inventory.html">Inventory</a>
        <a href="../maintenance.html">Maintenance</a>
        <a href="../search.html" id="current">Search</a>
        <!-- <a href="contact.html">Contact</a> -->
    </div>
    <div class="page">
        <?php
        $table = $_GET["table"];
        if ($table == "employees" || $table == "admins") {
            $id = $_GET["id"];
            $sql = "SELECT * FROM person WHERE id=$id";
            $furt = "SELECT * FROM $table WHERE id=$id";
        }else if($table == "items"){
            $barcode = $_GET["barcode"];
            $sql = "SELECT * FROM $table WHERE barcode=$barcode";
        }else if($table=="departments"){
            $d_id = $_GET["d_id"];
            $sql = "SELECT * FROM $table WHERE d_id=$d_id";
        }
        $result = mysqli_query($conn, $sql);
        $num = $result->field_count;
        $data = $result->fetch_row();

        if ($table == "admins" || $table == "employees") {
            $furt_result = mysqli_query($conn, $furt);
            $furt_num = $furt_result->field_count;
            $furt_data = $furt_result->fetch_row();
        }

        for ($count = 0; $count < $num; $count++) {
        ?>
            <ul style="margin-left: 200px;">
                <li>
                    <?php
                    $field = $result->fetch_field();
                    echo $field->name, ": ", $data[$count];
                    ?>
                </li>
            </ul>
        <?php
        }
        ?>
        <?php
        if ($table == "employees" || $table == "admins") {
            for ($count = 0; $count < $furt_num; $count++) {
        ?>
                <?php
                $field = $furt_result->fetch_field();
                if ($field->name == "id") {
                    continue;
                }
                ?>
                <ul style="margin-left: 200px;">
                    <li>
                        <?php
                        echo $field->name, ": ", $furt_data[$count];
                        ?>
                    </li>
                </ul>
        <?php
            }
        }
        ?>

        <p id="imprint">
            This website is student lab work and does not necessarily reflect Jacobs University Bremen opinions. Jacobs
            University Bremen does not endorse this site, nor is it checked by Jacobs University
            Bremen regularly, nor is it part of the official Jacobs University Bremen web presence.
            For each external link existing on this website, we initially have checked that the target page
            does not contain contents which is illegal wrt. German jurisdiction. However, as we have no influence on
            such contents, this may change without our notice. Therefore we deny any responsibility for the websites
            referenced through our external links from here.
            No information conflicting with GDPR is stored in the server.
        </p>
    </div>
</body>

</html>