package gui;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;

import javax.swing.JOptionPane;
import javax.swing.JTextPane;
import javax.swing.text.BadLocationException;
import javax.swing.text.StyledDocument;

import gnu.io.*;

public class ComPort implements SerialPortEventListener
{
	private static ComPort staticSerialPort = new ComPort();
	private String portName;
	private int baudrate;
	private String parity;
	private String stopBit;
	private String flowControl;
	private CommPort commPort;
	private static JTextPane console;
	
	/**
	* A BufferedReader which will be fed by a InputStreamReader 
	* converting the bytes into characters 
	* making the displayed results codepage independent
	*/
	private BufferedReader input;
	/** The output stream to the port */
	private OutputStream output;
	
	/*
	 * @brief: Private constructor
	 */
	private ComPort()
	{
	}

	/*
	 * @brief: Static instance method
	 */
	public static ComPort getInstance()
	{
		return staticSerialPort;
	}

	/*
	 * @brief:  Getters and setters
	 */
	public String getPortName() {
		return portName;
	}

	public void setPortName(String portName) {
		this.portName = portName;
	}

	public int getBaudrate() {
		return baudrate;
	}

	public void setBaudrate(int baudrate) {
		this.baudrate = baudrate;
	}

	public String getParity() {
		return parity;
	}

	public void setParity(String parity) {
		this.parity = parity;
	}

	public String getStopBit() {
		return stopBit;
	}

	public void setStopBit(String stopBit) {
		this.stopBit = stopBit;
	}

	public String getFlowControl() {
		return flowControl;
	}

	public void setFlowControl(String flowControl) {
		this.flowControl = flowControl;
	}

	public static JTextPane getConsole() {
		return console;
	}

	public static void setConsole(JTextPane console) {
		ComPort.console = console;
	}
	
	/*
	 * @brief: Check if connection is established or not
	 */
	public boolean isConnected()
	{
		try
		{			
			return CommPortIdentifier.getPortIdentifier(portName).isCurrentlyOwned();			
		}
		catch (Exception e)
		{
			JOptionPane.showMessageDialog(null, "Error: Can not check connection\n"
					+ "Error Info: " + e, "ERROR",
					JOptionPane.ERROR_MESSAGE);
			return false;
		}
	}

	/*
	 * @brief: Create a connection
	 */
	public boolean connect()
	{
		try 
		{
			CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
			if(portIdentifier.isCurrentlyOwned())
			{
				JOptionPane.showMessageDialog(null, "Error: Port is currently in use", "ERROR",
						JOptionPane.ERROR_MESSAGE);
				return false;
			}
			else
			{
				commPort = portIdentifier.open(this.getClass().getName(),2000);

				if (commPort instanceof SerialPort)
				{
					SerialPort serialPort = (SerialPort) commPort;
					int sb, p, fc;
					switch (stopBit)
					{
					case "1":
						sb = SerialPort.STOPBITS_1;
						break;
					case "1.5":
						sb = SerialPort.STOPBITS_1_5;
						break;
					case "2":
						sb = SerialPort.STOPBITS_2;
						break;
					default:
						sb = SerialPort.STOPBITS_1;
						break;
					}

					switch (parity)
					{
					case "None":
						p = SerialPort.PARITY_NONE;
						break;
					case "Odd":
						p = SerialPort.PARITY_ODD;
						break;
					case "Even":
						p = SerialPort.PARITY_EVEN;
						break;
					default:
						p = SerialPort.PARITY_NONE;
						break;

					}
					
					switch (flowControl)
					{
					case "None":
						fc = SerialPort.FLOWCONTROL_NONE;
						break;
					case "RTS/CTS IN":
						fc = SerialPort.FLOWCONTROL_RTSCTS_IN;
						break;
					case "RTS/CTS OUT":
						fc = SerialPort.FLOWCONTROL_RTSCTS_OUT;
						break;
					case "XON/XOFF IN":
						fc = SerialPort.FLOWCONTROL_XONXOFF_IN;
						break;
					case "XON/XOFF OUT":
						fc = SerialPort.FLOWCONTROL_XONXOFF_OUT;
						break;
					default:
						fc = SerialPort.FLOWCONTROL_NONE;
						break;
					}
					serialPort.setSerialPortParams(baudrate,
							SerialPort.DATABITS_8,
							sb,
							p);
					serialPort.setFlowControlMode(fc);
					
					input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
					output = serialPort.getOutputStream();
					
					// add event listeners
					serialPort.addEventListener(this);
					serialPort.notifyOnDataAvailable(true);
					return true;
				}
				else
				{
					JOptionPane.showMessageDialog(null, "Error: Only serial ports are handled by this program", "ERROR",
							JOptionPane.ERROR_MESSAGE);
					return false;
				}
			}
		} 
		catch (Exception e)
		{
			JOptionPane.showMessageDialog(null, "Error: Can not connect to " + portName +"\n"
					+ "Error: " + e, "ERROR", JOptionPane.ERROR_MESSAGE);
			return false;
		}
		
	}


	/*
	 * @brief: Disconnect from a serial port
	 */
	public void disconnect()
	{
		if(commPort instanceof SerialPort)
		{
			try
			{
				SerialPort serialPort = (SerialPort)commPort;
				input.close();
				output.close();
				serialPort.removeEventListener();
				serialPort.close();
			}
			catch (Exception e)
			{
				JOptionPane.showMessageDialog(null, "Error: Can not disconnect from COM", "ERROR",
						JOptionPane.ERROR_MESSAGE);
			}
		}
		else
		{
			JOptionPane.showMessageDialog(null, "Error: Only serial ports are handled by this program", "ERROR",
					JOptionPane.ERROR_MESSAGE);
		}

	}

	@Override
	public void serialEvent(SerialPortEvent event) {
		if (event.getEventType() == SerialPortEvent.DATA_AVAILABLE)
		{
			try
			{
				String inputLine = input.readLine();
				StyledDocument styledDocument = console.getStyledDocument();
//				Style style = console.addStyle(null, null);
//				StyleConstants.setForeground(style, Color.RED);				
		        try 
		        { 
		        	styledDocument.insertString(styledDocument.getLength(), inputLine + 
		        		System.getProperty("line.separator"), null);
		        }
		        catch (BadLocationException e)
		        {
		        }
			}
			catch (Exception e)
			{
				JOptionPane.showMessageDialog(null, "Error: " + e, "ERROR", JOptionPane.ERROR_MESSAGE);

			}
		}
		// Ignore all the other eventTypes, but you should consider the other ones.
		
	}
}
