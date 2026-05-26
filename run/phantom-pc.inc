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
		<!--
		<policy label="ahci -> "> <pci class="AHCI"/> </policy>
		-->

		<policy label="nvme0 -> " info="yes"> <pci class="NVME"/> </policy>
        <policy label="nvme1 -> " info="yes"> <pci class="NVME"/> </policy>
        <policy label="nvme2 -> " info="yes"> <pci class="NVME"/> </policy>

		<policy label_prefix="ps2"> <device name="ps2"/> </policy>
		<policy label_prefix="fb"  info="yes"> <pci class="VGA"/> </policy>
		<policy label_prefix="usb" info="yes"> <pci class="USB"/> </policy>
	</config>
</start>

<!--
<start name="ahci_report_rom">
	<binary name="report_rom"/>
	<resource name="RAM" quantum="1M"/>
	<provides> <service name="Report"/> <service name="ROM"/> </provides>
	<config verbose="yes"/>
</start>



<start name="ahci">
	<resource name="RAM" quantum="20M" />
	<provides><service name="Block" /></provides>
	<config atapi="no">
		<report ports="yes"/>
		<policy label="isomem -> " device="0" writeable="yes" />
		<policy label="vfs -> " device="1" writeable="yes" />
		<policy label="se_vfs -> " device="2" writeable="yes" />
-->
		<!-- <policy label="se_vault -> " device="0" writeable="yes" /> -->
		<!-- <defautl-policy device="0" writeable="yes" /> -->
<!--
	</config>
	<route>
		<service name="Report"> <child name="ahci_report_rom"/> </service>
		<any-service> <parent/> <any-child/> </any-service>
	</route>
</start>
-->

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
        <policy label="se_vfs -> " writeable="yes"/>
    </config>
    <route>
        <service name="Platform"> <child name="platform"/> </service>
        <service name="Timer">    <child name="timer"/>    </service>
        <any-service> <parent/> <any-child/> </any-service>
    </route>
</start>



<!--
<start name="vfs" ram="200M" caps="200">
  <provides><service name="File_system"/></provides>
  <config>
  
   	<vfs>
   		<dir name="dev">
   			<block name="block" block_buffer_count="128"/>
   		</dir>
      <lwext4 block_device="/dev/block" cache_write_back="yes"
              expand_via_io="no" writeable="yes"
              reporting="no"
              external_cache_size="32M" report_cache="yes"/>
   	</vfs>
   	<policy label_prefix="snapper" root="/" writeable="yes"/>
  </config>
  <route>
	<service name="Block"> <child name="nvme1"/> </service>
	<any-service> <parent/> <any-child/> </any-service>
  </route>
</start>
-->

	<!--
	<service name="Block"> <child name="ahci"/> </service>
    <service name="Block"> <child name="nvme1"/> </service>
	-->
 
<start name="snapper" ram="400M" caps="400">
  <!--
  <exit propagate="yes"/>
  -->
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

	<!--
		<service name="File_system"><child name="vfs"/></service>
		<service name="File_system"><child name="se_vault"/></service>
	-->
		<service name="File_system"><child name="se_vault"/></service>
		
		<!-- <service name="Block"><child name="ahci"/></service> -->
		<any-service> <parent/> <any-child /> </any-service>
	</route>
</start>



<start name="isomem" caps="2000">
 	<resource name="RAM" quantum="1G"/>
  
 	<config verbose="yes" ld_verbose="yes">
 	</config>
 	<route>
 		<!--
		<service name="Block"><child name="ahci"/></service>
		<service name="Block"><child name="nvme0"/></service>
		-->
		<service name="Block"><child name="nvme0"/></service>
 		<any-service> <parent/> <any-child /> </any-service>
 	</route>
</start>
 