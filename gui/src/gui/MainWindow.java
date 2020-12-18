package gui;

import javax.swing.JFrame;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.util.Enumeration;
import java.util.Timer;
import java.util.TimerTask;
import java.awt.event.ActionEvent;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JComboBox;
import javax.swing.SwingConstants;
import java.awt.Font;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.JPanel;
import javax.swing.border.LineBorder;
import javax.swing.text.DefaultCaret;

import gnu.io.CommPortIdentifier;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JTextPane;
import javax.swing.JScrollPane;

import org.knowm.xchart.QuickChart;
import org.knowm.xchart.XChartPanel;
import org.knowm.xchart.XYChart;
import java.awt.BorderLayout;
import javax.swing.JSplitPane;

public class MainWindow {

	private static JFrame frame;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				try {
					initialize();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private static void initialize() {
		frame = new JFrame();
		frame.setResizable(false);
		frame.setBounds(100, 100, 880, 688);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		
		JPanel serialPortControlPanel = new JPanel();
		serialPortControlPanel.setBorder(new LineBorder(new Color(0, 0, 0), 2, true));
		frame.getContentPane().add(serialPortControlPanel);
		serialPortControlPanel.setLayout(null);
		
		JComboBox<String> cbStopBit = new JComboBox<>();
		cbStopBit.setBounds(134, 143, 111, 23);
		serialPortControlPanel.add(cbStopBit);
		cbStopBit.setModel(new DefaultComboBoxModel<>(new String[] {"1", "1.5", "2"}));
		
		JLabel lblSerialPortControl = new JLabel("SERIAL PORT CONTROL");
		lblSerialPortControl.setHorizontalAlignment(SwingConstants.CENTER);
		lblSerialPortControl.setFont(new Font("Tahoma", Font.BOLD, 14));
		lblSerialPortControl.setBounds(10, 11, 201, 14);
		serialPortControlPanel.add(lblSerialPortControl);
		
		JLabel lbStatus = new JLabel("DISCONNECTED");
		lbStatus.setBounds(120, 199, 122, 28);
		serialPortControlPanel.add(lbStatus);
		lbStatus.setForeground(Color.RED);
		lbStatus.setFont(new Font("Tahoma", Font.BOLD, 13));
		lbStatus.setHorizontalAlignment(SwingConstants.CENTER);
		
		JComboBox<String> cbComPort = new JComboBox<>();
		cbComPort.setBounds(134, 35, 111, 23);
		serialPortControlPanel.add(cbComPort);
		
		JLabel lblComport = new JLabel("COMPORT");
		lblComport.setBounds(48, 45, 62, 14);
		serialPortControlPanel.add(lblComport);
		lblComport.setHorizontalAlignment(SwingConstants.RIGHT);
		
		JComboBox<String> cbBaudrate = new JComboBox<>();
		cbBaudrate.setBounds(134, 70, 111, 23);
		serialPortControlPanel.add(cbBaudrate);
		cbBaudrate.setModel(new DefaultComboBoxModel<>(new String[] {"110", "150", "300", "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200", "230400", "460800", "921600"}));
		
		JLabel lblBaudrate = new JLabel("BAUDRATE");
		lblBaudrate.setBounds(48, 79, 62, 14);
		serialPortControlPanel.add(lblBaudrate);
		lblBaudrate.setHorizontalAlignment(SwingConstants.RIGHT);
		
		JComboBox<String> cbParity = new JComboBox<>();
		cbParity.setBounds(134, 110, 111, 23);
		serialPortControlPanel.add(cbParity);
		cbParity.setModel(new DefaultComboBoxModel<>(new String[] {"None", "Odd", "Even"}));
		
		JLabel lblParity = new JLabel("PARITY");
		lblParity.setBounds(48, 113, 62, 14);
		serialPortControlPanel.add(lblParity);
		lblParity.setHorizontalAlignment(SwingConstants.RIGHT);
		
		JLabel lblStopBit = new JLabel("STOP BIT");
		lblStopBit.setBounds(48, 147, 62, 14);
		serialPortControlPanel.add(lblStopBit);
		lblStopBit.setHorizontalAlignment(SwingConstants.RIGHT);
		
		JButton btnConnect = new JButton("CONNECT");
		btnConnect.setBounds(20, 203, 103, 23);
		serialPortControlPanel.add(btnConnect);
		btnConnect.setForeground(Color.BLUE);
		btnConnect.setFont(new Font("Tahoma", Font.BOLD, 11));
		
		JLabel lblFlowControl = new JLabel("FLOW CONTROL");
		lblFlowControl.setHorizontalAlignment(SwingConstants.RIGHT);
		lblFlowControl.setBounds(10, 178, 100, 14);
		serialPortControlPanel.add(lblFlowControl);
		
		JComboBox<String> cbFlowControl = new JComboBox<>();
		cbFlowControl.setBounds(134, 175, 111, 20);
		serialPortControlPanel.add(cbFlowControl);
		cbFlowControl.setModel(new DefaultComboBoxModel<>(new String[] {"None", "RTS/CTS IN", "RTS/CTS OUT", "XON/XOFF IN", "XON/XOFF OUT"}));
		
		JTextPane console = new JTextPane();
		console.setFont(new Font("Tahoma", Font.BOLD, 13));
		console.setBackground(Color.BLACK);
		frame.getContentPane().add(console);
		ComPort.setConsole(console);
		DefaultCaret caret = (DefaultCaret) console.getCaret();
		caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);
		
		JScrollPane scrollPane = new JScrollPane(console, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
		        JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		scrollPane.setViewportBorder(new LineBorder(new Color(0, 0, 0), 2));
		frame.getContentPane().add(scrollPane);
		
		frame.getContentPane().setLayout(new BorderLayout(0, 0));
		double dataX[] = {0.0, 1.0, 2.0};
		double dataY[] = {0.0, 1.0, 2.0};
		XYChart chart = QuickChart.getChart("Response", "Time", "Position", "response", dataX, dataY);
		chart.getStyler().setLegendVisible(false);
		JPanel chartPanel = new XChartPanel<XYChart>(chart);
		frame.getContentPane().add(chartPanel, BorderLayout.CENTER);
		chartPanel.setLayout(null);
		
		JSplitPane splitPane = new JSplitPane(SwingConstants.VERTICAL, serialPortControlPanel, scrollPane);
		splitPane.setPreferredSize(new Dimension(0, 240));
		splitPane.setResizeWeight(0.35);
		frame.getContentPane().add(splitPane, BorderLayout.NORTH);
	
		btnConnect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0)
			{
				if(cbComPort.getItemCount() == 0)
				{
					JOptionPane.showMessageDialog(null, "Error: No COM port found", "ERROR",
							JOptionPane.ERROR_MESSAGE);
					btnConnect.setText("CONNECT");
					btnConnect.setForeground(Color.BLUE);
					lbStatus.setText("DISCONNECTED");
					lbStatus.setForeground(Color.RED);
				}
				else
				{
					ComPort comPort = ComPort.getInstance();
					comPort.setPortName(cbComPort.getSelectedItem().toString());
					if(btnConnect.getText() == "CONNECT" && !(comPort.isConnected()))
					{
						comPort.setBaudrate(Integer.parseInt(cbBaudrate.getSelectedItem().toString()));
						comPort.setParity(cbParity.getSelectedItem().toString());
						comPort.setStopBit(cbStopBit.getSelectedItem().toString());
						comPort.setFlowControl(cbFlowControl.getSelectedItem().toString());

						if(comPort.connect())
						{
							btnConnect.setText("DISCONNECT");
							btnConnect.setForeground(Color.RED);
							lbStatus.setText("CONNECTED");
							lbStatus.setForeground(Color.BLUE);
						}
						
					}
					else if(btnConnect.getText() == "DISCONNECT" && (comPort.isConnected()))
					{
						comPort.disconnect();
						btnConnect.setText("CONNECT");
						btnConnect.setForeground(Color.BLUE);
						lbStatus.setText("DISCONNECTED");
						lbStatus.setForeground(Color.RED);
					}
				}
			}
		});
		
		Timer timer = new Timer();
		timer.schedule(new TimerTask() {
			
			@Override
			public void run() {
				// Clear all items in cbComPort
				cbComPort.removeAllItems();
				
			    // Get list of ports available on this particular computer,
			    // by calling static method in CommPortIdentifier.
				@SuppressWarnings("unchecked")
				Enumeration<CommPortIdentifier> portList = CommPortIdentifier.getPortIdentifiers();
				
				// Process the list.
				while (portList.hasMoreElements())
				{
					CommPortIdentifier commPortIdentifier = (CommPortIdentifier)portList.nextElement();
					
					if (commPortIdentifier.getPortType() == CommPortIdentifier.PORT_SERIAL)
					{
						cbComPort.addItem("" + commPortIdentifier.getName());
					}
				}	
			}
		}, 0, 1000);
	}
}
