import java.sql.*;
import java.util.ArrayList;

public class SQLiteConnection {
    private static SQLiteConnection instance = null;
    private final Connection connection;
    private final Statement statement;

    public static SQLiteConnection getInstance() throws SQLException {
        if (instance == null) {
            instance = new SQLiteConnection();
        }
        return instance;
    }

    private SQLiteConnection() throws SQLException {
        this.connection = DriverManager.getConnection("jdbc:sqlite:database.db");
        this.connection.setAutoCommit(false);
        this.statement = this.connection.createStatement();
        String sql = "CREATE TABLE IF NOT EXISTS truck " +
                "(id INTEGER PRIMARY KEY," +
                " model TEXT, " +
                " capacity DOUBLE, " +
                " color TEXT, " +
                " weight DOUBLE, " +
                " cost DOUBLE);";
        statement.executeUpdate(sql);
        this.connection.commit();
    }

    public void createEntry(Truck truck) throws SQLException {
        String sql = "INSERT INTO Truck (model, capacity, color, weight, cost) VALUES (" + "'" + truck.getModel() + "', " +
                truck.getCapacity() + ", " +
                "'" + truck.getColor() + "', " +
                truck.getWeight() + ", " +
                truck.getCost() + ");";
        statement.executeUpdate(sql);
        this.connection.commit();
    }

    public void deleteEntry(Truck truck) throws SQLException {
        String sql = "DELETE FROM Truck WHERE model = '" + truck.getModel() + "' AND capacity = " + truck.getCapacity()
                + " AND color = '" + truck.getColor() + "' AND weight = " + truck.getWeight() + " AND cost = " + truck.getCost();
        statement.executeUpdate(sql);
        this.connection.commit();
    }

    public ArrayList<Truck> getInfo() throws SQLException {
        ArrayList<Truck> truckArrayList = new ArrayList<>();
        ResultSet resultSet = statement.executeQuery("SELECT model, capacity, color, weight, cost FROM truck");
        while (resultSet.next()){
            truckArrayList.add(new Truck.Builder().
                    setModel(resultSet.getString("model")).
                    setCapacity(resultSet.getDouble("capacity")).
                    setColor(resultSet.getString("color")).
                    setWeight(resultSet.getDouble("weight")).
                    setCost(resultSet.getDouble("cost")).
                    build());
        }
        return truckArrayList;
    }
}
