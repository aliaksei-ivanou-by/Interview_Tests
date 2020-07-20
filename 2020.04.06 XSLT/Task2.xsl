<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>
	<xsl:strip-space elements="*"/>
	
	<!-- identity transform -->
	<xsl:template match="@*|node()">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>
	
	<xsl:template match="str1">
		<xsl:call-template name="reverse">
			<xsl:with-param name="input" select="."/>
		</xsl:call-template>
	</xsl:template>
	
	<xsl:template name="reverse">
		<xsl:param name="input"/>
		<xsl:variable name="len" select="string-length($input)"/>
		<xsl:choose>
			<!-- Строки длиной меньше 2 обращаются тривиально -->
			<xsl:when test="$len &lt; 2">
				<xsl:value-of select="$input"/>
			</xsl:when>
			<!-- Строки длины 2 также обращаются тривиально -->
			<xsl:when test="$len = 2">
				<xsl:value-of select="substring($input,2,1)"/>
				<xsl:value-of select="substring($input,1,1)"/>
			</xsl:when>
			<xsl:otherwise>
				<!-- Шаблон рекурсивно применяется сначала ко второй,
            а потом к первой половине входной строки -->
				<xsl:variable name="mid" select="floor($len div 2)"/>
				<xsl:call-template name="reverse">
					<xsl:with-param name="input" select="substring($input,$mid+1,$mid+1)"/>
				</xsl:call-template>
				<xsl:call-template name="reverse">
					<xsl:with-param name="input" select="substring($input,1,$mid)"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	<xsl:template match="str2">
		<xsl:variable name="vnumsOnly" select=
			"translate(., translate(.,'0123456789',''), '')
			"/>
		
		<xsl:value-of select=
			"substring($vnumsOnly, (substring($vnumsOnly,1,1)='1') +1)"/>
	</xsl:template>
	
	<xsl:template match="str3">
		<xsl:variable name="withoutNums" select=
			"translate(., '1234567890', '')
			"/>
		
		<xsl:value-of select=
			"substring($withoutNums, (substring($withoutNums,1,1)='1') +1)"/>
	</xsl:template>
	
	<xsl:template match="str4">
		<xsl:value-of select="string-length(.)-string-length(translate(.,' ',''))+string-length(.)-string-length(translate(.,'\n',''))"/>
	</xsl:template>
	
</xsl:stylesheet>