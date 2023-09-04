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
        <div class="form">
            <form action="departments.php" method="post">
                <label for="num_of_emps">List all departments with employees greater than</label>
                <input type="number" id="num_of_emps" name="num_of_emps" style="width: 50px;">
                <input type="submit" name="submit">
            </form>
        </div>
        <?php
        if (isset($_POST["submit"])) {
            $num_of_emps = $_POST["num_of_emps"];
            $sql = "SELECT * FROM departments WHERE num_of_emps>$num_of_emps";
            $result = mysqli_query($conn, $sql);
            // echo "siiiiiiiiiiiiiiiiiiiiiiiiiiiuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuasjdhaskjdasdjaslkdaksdjalksjd     ".$sql;
            while ($row = $result->fetch_assoc()) {
        ?>
                <ul style="margin-left: 200px;">
                    <a href="./details.php?d_id=<?php echo $row["d_id"]; ?>&table=departments">
                        <li><?php echo $row["name"] ?></li>
                    </a>
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