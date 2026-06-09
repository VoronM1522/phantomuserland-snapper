<start name="pc_rtc">
  <resource name="RAM" quantum="1M"/>
  <provides>
    <service name="Rtc"/>
  </provides>
</start>

<start name="report_rom">
	<resource name="RAM" quantum="2M"/>
	<provides> <service name="Report"/> <service name="ROM"/> </provides>
	<config>
		<policy label="pci_decode -> system"    report="acpi -> acpi"/>
		<policy label="platform -> devices" report="pci_decode -> devices"/>
		<policy label="usb_hid -> report"    report="usb -> devices"/>
		<default-policy report="usb -> usb -> devices"/>
	</config>
</start>


<start name="acpi" caps="350">
	<resource name="RAM" quantum="4M"/>
	<route>
		<service name="Report"> <child name="report_rom"/> </service>
		<any-service> <parent/> <any-child /> </any-service>
	</route>
</start>

<start name="pci_decode" caps="350">
	<resource name="RAM" quantum="2M"/>
	<route>
		<service name="Report">             <child name="report_rom"/> </service>
		<service name="ROM" label="system"> <child name="report_rom"/> </service>
		<any-service> <parent/> <any-child /> </any-service>
	</route>
</start>

<start name="platform" ram="300M" caps="200" managing_system="yes">
	<provides>
		<service name="Platform"/>
	</provides>
	<route>
		<service name="ROM" label="devices"> <child name="report_rom"/> </service>
		<service name="Report"> <child name="report_rom"/> </service>
		<any-service> <parent/> <any-child /> </any-service>
	</route>
	<config>
		<report devices="yes"/>
		<policy label="nvme0 -> " info="yes"> <pci class="NVME"/> </policy>
        <policy label="nvme1 -> " info="yes"> <pci class="NVME"/> </policy>
        <policy label="nvme2 -> " info="yes"> <pci class="NVME"/> </policy>
		<policy label="nvme3 -> " info="yes"> <pci class="NVME"/> </policy>
		<policy label_prefix="ps2"> <device name="ps2"/> </policy>
		<policy label_prefix="fb"  info="yes"> <pci class="VGA"/> </policy>
		<policy label_prefix="usb" info="yes"> <pci class="USB"/> </policy>
	</config>
</start>


<start name="nvme0" caps="120" ram="24M">
	<binary name="nvme"/>
    <provides><service name="Block"/></provides>
    <config>
        <policy label="isomem -> " writeable="yes"/>
    </config>
    <route>
        <service name="Platform"> <child name="platform"/> </service>
        <service name="Timer">    <child name="timer"/>    </service>
        <any-service> <parent/> <any-child/> </any-service>
    </route>
</start>

<start name="nvme1" caps="120" ram="24M">
	<binary name="nvme"/>
    <provides><service name="Block"/></provides>
    <config>
        <policy label="vfs -> " writeable="yes"/>
    </config>
    <route>
        <service name="Platform"> <child name="platform"/> </service>
        <service name="Timer">    <child name="timer"/>    </service>
        <any-service> <parent/> <any-child/> </any-service>
    </route>
</start>

<start name="nvme2" caps="120" ram="24M">
	<binary name="nvme"/>
    <provides><service name="Block"/></provides>
    <config>
        <default-policy writeable="yes"/>
    </config>
    <route>
        <service name="Platform"> <child name="platform"/> </service>
        <service name="Timer">    <child name="timer"/>    </service>
        <any-service> <parent/> <any-child/> </any-service>
    </route>
</start>


<start name="nvme3" caps="120" ram="24M">
	<binary name="nvme"/>
    <provides><service name="Block"/></provides>
    <config>
        <policy label="usb_sec_fs -> " writeable="yes"/>
    </config>
    <route>
        <service name="Platform"> <child name="platform"/> </service>
        <service name="Timer">    <child name="timer"/>    </service>
        <any-service> <parent/> <any-child/> </any-service>
    </route>
</start>

 
<start name="snapper" ram="400M" caps="400">
  <provides>
    <service name="Snapper"/>
  </provides>

  <config
      verbose="true"
      redundancy="2"
      integrity="true"
      max_snapshots="0" 
      min_snapshots="0" 
      threshold="1000"
      expiration="3600"
      bufsize="100M">
	  <!--
	  max_snapshots="5" 
      min_snapshots="1"
	  -->

    <rtc/>

    <vfs>
      <fs/>	  
    </vfs>
  </config>
	<route>
		<service name="File_system"><child name="se_vault"/></service>
		<any-service> <parent/> <any-child /> </any-service>
	</route>
</start>



<start name="isomem" caps="2000">
 	<resource name="RAM" quantum="1G"/>
  
 	<config verbose="yes" ld_verbose="yes">
 	</config>
 	<route>
		<service name="Block"><child name="nvme0"/></service>
 		<any-service> <parent/> <any-child /> </any-service>
 	</route>
</start>
 