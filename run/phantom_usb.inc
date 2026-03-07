<start name="usb_block" ram="64M">
  <provides> <service name="USB_Block"/> </provides>
  <config label="usb_stick" report="yes" writeable="yes" interface="0"
          alt_setting="0" lun="0" reset_device="no" verbose_scsi="no"/>
  <route>
   <service name="Usb"> <child name="usb"/> </service>
   <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>

<!--
<start name="usb" ram="12M">
  <provides><service name="Usb"/></provides>
  <config>
    <raw>
        <policy label="usb_block -> usb_stick" vendor_id="0x8564" product_id="0x1000"/>
    </raw>
  </config>
</start>
-->

<start name="usb" caps="1500" ram="20M" managing_system="yes">
		<binary name="init"/>
		<provides> <service name="Usb"/> </provides>
		<route>
			<service name="ROM" label="config">
				<parent label="drivers.config"/> </service>
			<service name="Report"> <child name="report_rom"/> </service>
			<service name="Timer">  <child name="timer"/> </service>
			<any-service> <parent/> </any-service>
		</route>
	</start> 

<!--
<start name="tresor" caps="200">
	<resource name="RAM" quantum="8M"/>
	<provides>
		<service name="Block"/>
	</provides>
  <config>
		<key file="/some/path/key.bin"/>
	</config>

	<route>
		<service name="Block" label="raw"> <child name="usb_block_drv"/> </service>
		<any-service> <parent/> <any-child/> </any-service>
	</route>
</start>

<start name="report_rom">
		<provides> <service name="Report"/> <service name="ROM"/> </provides>
		<config verbose="yes">
			<default-policy report="usb -> usb -> devices"/>
		</config>
	</start> 
-->



<start name="trust_anchor_fs" caps="200" ram="10M">
			<binary name="vfs"/>
			<provides><service name="File_system_TA"/></provides>
			<config>
				<vfs>
					<dir name="storage">
						<ram/>
					</dir>

					<dir name="dev"> 
						<tresor_trust_anchor name="tresor_trust_anchor" storage_dir="/storage"/>
					</dir>
				</vfs>

				<default-policy root="/dev/tresor_trust_anchor" writeable="yes"/>
			</config>
			<route>
				<service name="PD">  <parent/> </service>
				<service name="ROM"> <parent/> </service>
				<service name="LOG"> <parent/> </service>
				<service name="CPU"> <parent/> </service>
			</route>
		</start>