<!--
<start name="usb_host" ram="10M">
  <binary name="pc_usb_host"/>
  <provides><service name="Usb"/></provides>
  <config>
     <policy>
       <device vendor_id="0x8564" product_id="0x1000"/>
     </policy>
  </config>
</start>
-->



<start name="usb_sec" ram="4M">
  <binary name="usb_block"/>
  <provides> <service name="USB_Block"/> </provides>
  <config label="usb_drive" report="yes" writeable="yes" interface="0"
          alt_setting="0" lun="0" reset_device="no" verbose_scsi="no"/>
  <route>
   <service name="Usb"> <child name="usb"/> </service>
   <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>


















<!--
	<start name="usb" caps="1500" ram="32M" managing_system="yes">
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

	<start name="usb_block" ram="4M">
		<provides> <service name="Block"/> </provides>
		<config report="yes" writeable="no"/>
		<route>
			<service name="Usb">    <child name="usb"/> </service>
			<service name="Report"> <child name="report_rom"/> </service>
			<any-service> <parent/> <any-child/> </any-service>
		</route>
	</start>
-->





































<!--
<start name="usb_block" ram="64M">
  <provides> <service name="USB_Block"/> </provides>
  <config label="usb_stick" report="yes" writeable="no" interface="0"
          alt_setting="0" lun="0" reset_device="no" verbose_scsi="no"/>
		  <config>
				<policy label="usb_block -> ">
				<devices>
					<device vendor="QEMU" product="QEMU USB HARDDRIVE" block_size="512" block_count="31703040" writeable="yes"/>
				</devices>
				<device name="usb-1-2"/>
				</policy>
		</config>
  <route>
   <service name="Usb"> <child name="usb"/> </service>
   <any-service> <parent/> <any-child/> </any-service>
  </route>

</start>



	<start name="usb" caps="1500" ram="64M" managing_system="yes">
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
-->

<!--
<start name="usb" caps="1500" ram="20M" managing_system="yes">
		<binary name="init"/>
		<provides> <service name="Usb"/> </provides>
		<config>
		<policy label="usb_block -> ">
			<devices>
				<device vendor="QEMU" product="QEMU USB HARDDRIVE" block_size="512" block_count="31703040" writeable="no"/>
			</devices>
		</policy>
		</config>
		<route>
			<service name="ROM" label="config">
				<parent label="drivers.config"/> </service>
			<service name="Report"> <child name="report_rom"/> </service>
			<service name="Timer">  <child name="timer"/> </service>
			<any-service> <parent/> </any-service>
		</route>
	</start> 
-->




<!--
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
-->