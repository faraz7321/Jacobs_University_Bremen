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
        <a href="../about.php">About</a>
        <a href="../imprint.php">Imprint</a>
        <?php
        session_start();
        if ($_SESSION["loggedin"]) { ?>
            <a href="../logout.php">Logout</a>
        <?php } ?>
    </div>

    <div class="sidebar">
        <a href="../home.php">
            <img src="../images/favicon.png" alt="logo">
        </a>
        <a href="../home.php" id="current">Home</a>
        <a href="../inventory.php">Inventory</a>
        <?php if ($_SESSION["loggedin"]) { ?>
            <a href="../maintenance.php">Maintenance</a>
        <?php } ?>
        <a href="../search.php">Search</a>
        <!-- <a href="contact.html">Contact</a> -->
    </div>
    <div class="page">
        <div class="form">
            <form action="items.php" method="post">
                <label for="department">List all items in</label>
                <select name="cname" id="category" required>
                    <option value="none" selected disabled>Choose a Category</option>
                    <?php
                    $sql = mysqli_query($conn, "SELECT c_name FROM categories;");
                    while ($row = $sql->fetch_assoc()) {
                    ?>
                        <option><?php echo $row["c_name"]; ?></option>
                    <?php
                    }
                    ?>
                </select>
                <!-- <input type="name" name="d_name" placeholder="Name"> -->
                <input type="submit" value="Search" name="submit" style="margin-left: 293px; text-align:center;">
            </form>
        </div>
        <div class="results">
            <?php
            if (isset($_POST["submit"])) {
                $c_name = $_POST["cname"];
                $sql = "SELECT c_id FROM categories WHERE c_name='$c_name'";
                $result = mysqli_query($conn, $sql);
                $row = $result->fetch_assoc();
                $c_id = $row["c_id"];
                $sql = "SELECT * FROM items WHERE c_id=$c_id";
                $items = mysqli_query($conn, $sql);
                echo "<ul style='margin-left: 200px;'>";
                while ($row = $items->fetch_assoc()) {
            ?>
                    <a href="./details.php?barcode=<?php echo $row["barcode"]; ?>&table=items">
                        <li>
                            <?php
                            echo $row["item_name"];
                            ?>
                        </li>
                    </a>
            <?php
                }
            }
            ?>
            </ul>
        </div>






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