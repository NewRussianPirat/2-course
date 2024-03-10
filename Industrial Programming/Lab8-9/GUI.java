import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Vector;

public class GUI {
    private static GUI instance = null;

    private final static String[] ColumnNames = { "Model", "Capacity", "Color", "Weight", "Cost"};
    private static final String[][] table = new String[0][5];

    private static final JFrame jFrame = new JFrame("Truck Factory");

    private static final JButton exitButton = new JButton(new ExitAction());
    private static final JButton addButton = new JButton(new AddAction());
    private static final JButton deleteButton = new JButton(new DeleteAction());
    private static final JButton showTableButton = new JButton(new ShowTableAction());
    private static final JButton hideTableButton = new JButton(new HideTableAction());

    private static final JLabel welcomeLabel = new JLabel("Welcome to my Truck creator!", SwingConstants.CENTER);
    private static final JLabel tableLabel = new JLabel("Here are the trucks you made", SwingConstants.CENTER);

    private static final BufferedImage TruckImageBuffered;

    private static final DefaultTableModel tableModel = new DefaultTableModel(table, ColumnNames);
    private static final JTable jTable = new JTable(tableModel) {
        @Override
        public boolean isCellEditable(int i, int i1) {
            return false;
        }
    };
    private static final JScrollPane jScrollPane= new JScrollPane(jTable);

    private static final MyJPanel jPanel = new MyJPanel();

    private static final Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();

    static {
        try {
            TruckImageBuffered = ImageIO.read(new File("img/truck.png"));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static final SQLiteConnection sqliteConnection;

    static {
        try {
            sqliteConnection = SQLiteConnection.getInstance();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private GUI() {}

    public static GUI getInstance() {
        if (instance == null) {
            instance = new GUI();
        }
        return instance;
    }

    private static class MyJPanel extends JComponent {
        @Override
        protected void paintComponent(Graphics g) {
            Graphics2D g2 = (Graphics2D) g;
            this.setBounds(0, 0, jFrame.getWidth(), jFrame.getHeight());

            Image truckImage = TruckImageBuffered.getScaledInstance(this.getWidth(), this.getHeight(), Image.SCALE_DEFAULT);

            jScrollPane.setBounds(250, 125, this.getWidth() - 500, this.getHeight() - 250);
            g2.drawImage(truckImage, 0, 0, null);

            exitButton.setBounds(this.getWidth() - 150, this.getHeight() - 100, 80, 40);
            addButton.setBounds(this.getX() + 50, this.getHeight() - 100, 120, 40);
            deleteButton.setBounds(this.getX() + 200, this.getHeight() - 100, 120, 40);
            showTableButton.setBounds(this.getWidth() / 2 - 60, this.getHeight() - 100, 120, 40);
            hideTableButton.setBounds(this.getWidth() / 2 - 60, this.getHeight() - 100, 120, 40);

            welcomeLabel.setBounds(this.getWidth() / 2 - 150, 20, 300, 40);
            welcomeLabel.setFont(new Font("Arial", Font.BOLD, 20));
            tableLabel.setBounds(250, 80, this.getWidth() - 500, 40);
            tableLabel.setFont(new Font("Arial", Font.BOLD, 20));

            setLayout(null);
        }
    }

    public void createGUI() throws SQLException {
        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jFrame.setBounds(dimension.width / 2 - 600, dimension.height / 2 - 300, 1200, 600);
        jFrame.setMinimumSize(new Dimension(1200, 600));

        addButton.setVisible(false);
        deleteButton.setVisible(false);
        hideTableButton.setVisible(false);
        exitButton.setText("Exit");
        addButton.setText("Add truck");
        deleteButton.setText("Remove truck");
        showTableButton.setText("Show table");
        hideTableButton.setText("Hide table");

        tableLabel.setVisible(false);

        jScrollPane.setVisible(false);

        ArrayList<Truck> truckArrayList = sqliteConnection.getInfo();
        for (Truck truck : truckArrayList) {
            tableModel.addRow(new String[] {
                    truck.getModel(),
                    Double.toString(truck.getCapacity()),
                    truck.getColor(),
                    Double.toString(truck.getWeight()),
                    Double.toString(truck.getCost())
            });
        }

        jFrame.add(exitButton);
        jFrame.add(addButton);
        jFrame.add(deleteButton);
        jFrame.add(showTableButton);
        jFrame.add(hideTableButton);
        jFrame.add(welcomeLabel);
        jFrame.add(tableLabel);
        jFrame.add(jScrollPane);
        jFrame.add(jPanel);

        jFrame.setVisible(true);
    }

    private static class ExitAction extends AbstractAction {
        @Override
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }

    private static class ShowTableAction extends AbstractAction {
        @Override
        public void actionPerformed(ActionEvent e) {
            jScrollPane.setVisible(true);
            tableLabel.setVisible(true);
            showTableButton.setVisible(false);
            hideTableButton.setVisible(true);
            addButton.setVisible(true);
            deleteButton.setVisible(true);
        }
    }

    private static class HideTableAction extends AbstractAction {
        @Override
        public void actionPerformed(ActionEvent e) {
            jScrollPane.setVisible(false);
            tableLabel.setVisible(false);
            hideTableButton.setVisible(false);
            addButton.setVisible(false);
            deleteButton.setVisible(false);
            showTableButton.setVisible(true);
        }
    }

    private static class DeleteAction extends AbstractAction {
        @Override
        public void actionPerformed(ActionEvent e) {
            JDialog jDialog = new JDialog(jFrame, "Removing truck",true);
            jDialog.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
            jDialog.setResizable(false);
            jDialog.setBounds(dimension.width / 2 - 300, dimension.height / 2 - 200, 600, 400);
            jDialog.setLayout(null);

            ArrayList<Truck> truckArrayList;
            try {
                truckArrayList = sqliteConnection.getInfo();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            Vector<Truck> vector = new Vector<>(truckArrayList);

            JList<Truck> truckJList = new JList<>(vector);
            JScrollPane jScrollPane1 = new JScrollPane(truckJList);
            jScrollPane1.setBounds(50, 50, 500, 200);

            JLabel jLabel = new JLabel("Choose a truck to remove", SwingConstants.CENTER);
            jLabel.setBounds(50, 20, 500, 20);

            JButton jDialogExitButton = new JButton();
            jDialogExitButton.addActionListener(e1 ->
                    jDialog.dispatchEvent(new WindowEvent(jDialog, WindowEvent.WINDOW_CLOSING)));
            jDialogExitButton.setBounds(430, 300, 120, 40);
            jDialogExitButton.setText("Cancel");

            JButton jDialogDeleteButton = new JButton();
            jDialogDeleteButton.addActionListener(e1 -> {
                Truck truck = truckJList.getSelectedValue();
                for (int i = 0; i < jTable.getRowCount(); ++i) {
                    if (Objects.equals(jTable.getValueAt(i, 0).toString(), truck.getModel()) &&
                            Double.parseDouble(jTable.getValueAt(i, 1).toString()) == truck.getCapacity() &&
                            Objects.equals(jTable.getValueAt(i, 2).toString(), truck.getColor()) &&
                            Double.parseDouble(jTable.getValueAt(i, 3).toString()) == truck.getWeight() &&
                            Double.parseDouble(jTable.getValueAt(i, 4).toString()) == truck.getCost()) {
                        tableModel.removeRow(i);
                        try {
                            sqliteConnection.deleteEntry(truck);
                            break;
                        } catch (SQLException ex) {
                            throw new RuntimeException(ex);
                        }
                    }
                }
                jDialog.dispatchEvent(new WindowEvent(jDialog, WindowEvent.WINDOW_CLOSING));
            });
            jDialogDeleteButton.setBounds(70, 300, 120, 40);
            jDialogDeleteButton.setText("Remove truck");

            jDialog.add(jScrollPane1);
            jDialog.add(jLabel);
            jDialog.add(jDialogExitButton);
            jDialog.add(jDialogDeleteButton);

            jDialog.setVisible(true);
        }
    }

    private static class AddAction extends AbstractAction {
        @Override
        public void actionPerformed(ActionEvent e) {
            JDialog jDialog = new JDialog(jFrame, "Adding truck", true);
            JPanel jPanel1 = new JPanel();
            jDialog.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
            jDialog.setResizable(false);
            jDialog.setBounds(dimension.width / 2 - 300, dimension.height / 2 - 200, 600, 400);

            jPanel1.setLayout(null);
            jPanel1.setBounds(0, 0, 600, 400);

            JButton jDialogExitButton = new JButton();
            jDialogExitButton.addActionListener(e1 ->
                    jDialog.dispatchEvent(new WindowEvent(jDialog, WindowEvent.WINDOW_CLOSING)));
            jDialogExitButton.setBounds(430, 300, 120, 40);
            jDialogExitButton.setText("Cancel");

            JTextField modelField = new JTextField();
            JTextField capacityField = new JTextField();
            JTextField colorField = new JTextField();
            JTextField weightField = new JTextField();
            JTextField costField = new JTextField();
            modelField.setBounds(100, 38, 300, 20);
            capacityField.setBounds(100, 88, 300, 20);
            colorField.setBounds(100, 138, 300, 20);
            weightField.setBounds(100, 188, 300, 20);
            costField.setBounds(100, 238, 300, 20);

            JLabel modelLabel = new JLabel("Set model: ");
            modelLabel.setBounds(20, 20, 80, 50);
            JLabel capacityLabel = new JLabel("Set capacity: ");
            capacityLabel.setBounds(20, 70, 80, 50);
            JLabel colorLabel = new JLabel("Set color: ");
            colorLabel.setBounds(20, 120, 80, 50);
            JLabel weightLabel = new JLabel("Set weight: ");
            weightLabel.setBounds(20, 170, 80, 50);
            JLabel costLabel = new JLabel("Set cost: ");
            costLabel.setBounds(20, 220, 80, 50);

            JButton jDialogAddButton = new JButton();
            jDialogAddButton.addActionListener(e1 -> {
                try {
                    Double.parseDouble(capacityField.getText());
                    Double.parseDouble(weightField.getText());
                    Double.parseDouble(costField.getText());
                }
                catch (NumberFormatException exception) {
                    JDialog ErrorWindow = new JDialog(jDialog, "Error!",true);
                    ErrorWindow.setResizable(false);
                    ErrorWindow.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
                    ErrorWindow.setLayout(null);
                    ErrorWindow.setBounds(dimension.width / 2 - 150, dimension.height / 2 - 100, 300, 200);

                    JLabel errorLabel = new JLabel("The entered data was incorrect!", SwingConstants.CENTER);
                    errorLabel.setBounds(20, 50, 260, 20);

                    JButton errorButton = new JButton("Ok");
                    errorButton.setBounds(120, 110, 60, 40);
                    errorButton.addActionListener(e2 -> {
                        errorButton.dispatchEvent(new WindowEvent(jDialog, WindowEvent.WINDOW_CLOSING));
                        jDialog.dispatchEvent(new WindowEvent(jDialog, WindowEvent.WINDOW_CLOSING));
                    });

                    ErrorWindow.add(errorLabel);
                    ErrorWindow.add(errorButton);
                    ErrorWindow.setVisible(true);
                    return;
                }
                tableModel.addRow(new String[] {
                        modelField.getText(),
                        capacityField.getText(),
                        colorField.getText(),
                        weightField.getText(),
                        costField.getText()
                });

                Truck truck = new Truck.Builder().
                        setModel(modelField.getText()).
                        setCapacity(Double.parseDouble(capacityField.getText())).
                        setColor(colorField.getText()).
                        setWeight(Double.parseDouble(weightField.getText())).
                        setCost(Double.parseDouble(costField.getText())).
                        build();

                try {
                    sqliteConnection.createEntry(truck);
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }

                jDialog.dispatchEvent(new WindowEvent(jDialog, WindowEvent.WINDOW_CLOSING));
            });
            jDialogAddButton.setBounds(70, 300, 120, 40);
            jDialogAddButton.setText("Add truck");

            jPanel1.add(modelLabel);
            jPanel1.add(capacityLabel);
            jPanel1.add(colorLabel);
            jPanel1.add(weightLabel);
            jPanel1.add(costLabel);
            jPanel1.add(modelField);
            jPanel1.add(capacityField);
            jPanel1.add(colorField);
            jPanel1.add(weightField);
            jPanel1.add(costField);
            jPanel1.add(jDialogExitButton);
            jPanel1.add(jDialogAddButton);

            jDialog.add(jPanel1);
            jDialog.setLayout(null);
            jDialog.setVisible(true);
        }
    }
}