/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



package org.openoffice.xmerge.converter.xml.sxc.pexcel.records;

import java.io.OutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.awt.Point;

import org.openoffice.xmerge.util.Debug;
import org.openoffice.xmerge.util.EndianConverter;
import org.openoffice.xmerge.converter.xml.sxc.pexcel.PocketExcelConstants;


/**
 * Represents a BIFF Record that describes the selected area of a worksheet
 */
public class Selection implements BIFFRecord {

    private byte[] rwTop		= new byte[2];
    private byte   colLeft;
    private byte[] rwBottom		= new byte[2];
    private byte   colRight;
    private byte[] rwActive		= new byte[2];
    private byte   colActive;
    
	/**
	 * Default Constructor
	 */
    public Selection() {
    	this.rwTop			= EndianConverter.writeShort((short) 0);
    	this.colLeft		= 0; 
    	this.rwBottom		= EndianConverter.writeShort((short) 0);
    	this.colRight		= 0; 
    	this.rwActive		= EndianConverter.writeShort((short) 0);
    	this.colActive		= 0; 
		
    }

	/**
	 * Constructs a Selection Record from the <code>InputStream</code> 
	 *
	 * @param	is InputStream containing a Pocket Excel Data file.
	 */
    public Selection(InputStream is) throws IOException {
		read(is);	
    }

    /**
	 * Get the hex code for this particular <code>BIFFRecord</code> 
	 *
	 * @return the hex code for <code>Selection</code>
	 */
    public short getBiffType() {
        return PocketExcelConstants.CURRENT_SELECTION;
    }
	
    public Point getActiveCell() {
		Point p = new Point(colActive, EndianConverter.readShort(rwActive));
        return p;
    } 
	
    public void setActiveCell(Point p) {

		colActive = (byte) p.getX();
		rwActive = EndianConverter.writeShort((short) p.getY());
    }
	
	/**
	 * Reads a Selection Record from the <code>InputStream</code> 
	 *
	 * @param	input InputStream containing a Pocket Excel Data file.
	 */
    public int read(InputStream input) throws IOException {
		
        int numOfBytesRead	= input.read(rwTop);
        colLeft				+= (byte) input.read();
        numOfBytesRead		+= input.read(rwBottom);
        colRight			+= (byte) input.read();
        numOfBytesRead		+= input.read(rwActive);
        colActive			+= (byte) input.read();
		numOfBytesRead += 3;
                
        Debug.log(Debug.TRACE,"\trwTop : "+ EndianConverter.readShort(rwTop) + 
                            " colLeft : " + colLeft +
                            " rwBottom : " + EndianConverter.readShort(rwBottom) +
                            " colRight : "+ colRight + 
                            " rwActive : " + EndianConverter.readShort(rwActive) +
                            " colActive : " + colActive);
        
        return numOfBytesRead;                
    }
    
    public void write(OutputStream output) throws IOException {

		output.write(getBiffType());
		output.write(rwTop);
		output.write(colLeft);
		output.write(rwBottom);
		output.write(colRight);
		output.write(rwActive);
		output.write(colActive);

		Debug.log(Debug.TRACE,"Writing Selection record");
    }
    
}
