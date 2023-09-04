<html>
    <head>
        <title>igdfg</title>
    <head>

    <body>

        <?php
        $_SERVER = "localhost";
        $myusername = "group30";
        $mypassword = "apachewhich";
        $dbName = "group30";

        // create connection
        $conn = mysqli_connect($_SERVER, $myusername, $mypassword, $dbName);
        if (mysqli_connect_errno()) {
            echo "Failed to connect to DB!";
            exit();
        }
        ?>
    <body>
</html>