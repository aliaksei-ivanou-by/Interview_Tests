<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:str="http://exslt.org/strings" xmlns:exsl="http://exslt.org/common" version="1.0"
  exclude-result-prefixes="str exsl" xmlns:ext="http://exslt.org/common">

  <xsl:output method="xml" indent="yes"/>

  <xsl:strip-space elements="*"/>
  <xsl:template match="/">
    <touristInfo>
      <xsl:call-template name="processing1"/>
    </touristInfo>
  </xsl:template>

  <xsl:template match="list/tourists//*" name="processing1">
    <xsl:for-each select="list/tourists">
      <touristGroup>
        <xsl:variable name="tourist">
          <xsl:call-template name="str:tokenize">
            <xsl:with-param name="string" select="."/>
            <xsl:with-param name="delimiters" select="'|'"/>
          </xsl:call-template>
        </xsl:variable>
        <xsl:for-each select="exsl:node-set($tourist)/*">
          <xsl:call-template name="processing2"/>
        </xsl:for-each>
      </touristGroup>
    </xsl:for-each>
  </xsl:template>

  <xsl:template name="processing2">
    <tourist>
      <xsl:variable name="tourist">
        <xsl:call-template name="str:tokenize">
          <xsl:with-param name="string" select="."/>
          <xsl:with-param name="delimiters" select="'/'"/>
        </xsl:call-template>
      </xsl:variable>
      <xsl:for-each select="exsl:node-set($tourist)/tourist[1]">
          <xsl:choose>
            <xsl:when test="exsl:node-set($tourist)/tourist[1] = '7'">
              <xsl:attribute name="type">
              <xsl:text>INF</xsl:text>
              </xsl:attribute>
            </xsl:when>
            <xsl:when test="exsl:node-set($tourist)/tourist[1] = '8'">
              <xsl:attribute name="type">
              <xsl:text>CHD</xsl:text>
              </xsl:attribute>
            </xsl:when>
            <xsl:when test="exsl:node-set($tourist)/tourist[1] = '10'">
              <xsl:attribute name="type">
              <xsl:text>ADT</xsl:text>
              </xsl:attribute>
            </xsl:when>
          </xsl:choose>
      </xsl:for-each>
      <xsl:for-each select="exsl:node-set($tourist)/tourist[2]">
          <xsl:choose>
            <xsl:when test="exsl:node-set($tourist)/tourist[2] != 'null'">
              <xsl:attribute name="birthDate">
              <xsl:value-of select="."/>
              </xsl:attribute>
            </xsl:when>
          </xsl:choose>
      </xsl:for-each>
      <xsl:for-each select="exsl:node-set($tourist)/tourist[5]">
        <prefix>
          <xsl:value-of select="."/>
        </prefix>
      </xsl:for-each>
      <xsl:for-each select="exsl:node-set($tourist)/tourist[4]">
        <name>
          <xsl:value-of select="."/>
        </name>
      </xsl:for-each>
      <xsl:for-each select="exsl:node-set($tourist)/tourist[3]">
        <surname>
          <xsl:value-of select="."/>
        </surname>
      </xsl:for-each>
    </tourist>
  </xsl:template>

  <xsl:template name="str:tokenize">
    <xsl:param name="string" select="''"/>
    <xsl:param name="delimiters" select="' &#x9;&#xA;'"/>
    <xsl:choose>
      <xsl:when test="not($string)"/>
      <xsl:when test="not($delimiters)">
        <xsl:call-template name="str:_tokenize-characters">
          <xsl:with-param name="string" select="$string"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:call-template name="str:_tokenize-delimiters">
          <xsl:with-param name="string" select="$string"/>
          <xsl:with-param name="delimiters" select="$delimiters"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="str:_tokenize-characters">
    <xsl:param name="string"/>
    <xsl:if test="$string">
      <tourist>
        <xsl:value-of select="substring($string, 1, 1)"/>
      </tourist>
      <xsl:call-template name="str:_tokenize-characters">
        <xsl:with-param name="string" select="substring($string, 2)"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

  <xsl:template name="str:_tokenize-delimiters">
    <xsl:param name="string"/>
    <xsl:param name="delimiters"/>
    <xsl:variable name="delimiter" select="substring($delimiters, 1, 1)"/>
    <xsl:choose>
      <xsl:when test="not($delimiter)">
        <tourist>
          <xsl:value-of select="$string"/>
        </tourist>
      </xsl:when>
      <xsl:when test="contains($string, $delimiter)">
        <xsl:if test="not(starts-with($string, $delimiter))">
          <xsl:call-template name="str:_tokenize-delimiters">
            <xsl:with-param name="string" select="substring-before($string, $delimiter)"/>
            <xsl:with-param name="delimiters" select="substring($delimiters, 2)"/>
          </xsl:call-template>
        </xsl:if>
        <xsl:call-template name="str:_tokenize-delimiters">
          <xsl:with-param name="string" select="substring-after($string, $delimiter)"/>
          <xsl:with-param name="delimiters" select="$delimiters"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:call-template name="str:_tokenize-delimiters">
          <xsl:with-param name="string" select="$string"/>
          <xsl:with-param name="delimiters" select="substring($delimiters, 2)"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>