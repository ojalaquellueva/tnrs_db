CREATE TABLE reference (
  referenceID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  identifier VARCHAR(250) DEFAULT NULL,
  bibliographicCitationVerbatim VARCHAR(500) DEFAULT NULL,
  title VARCHAR(250) DEFAULT NULL,
  authors VARCHAR(250) DEFAULT NULL,
  publicationYear VARCHAR(12) DEFAULT NULL,
  issue VARCHAR(12) DEFAULT NULL,
  pages VARCHAR(12) DEFAULT NULL,
  publisher VARCHAR(250) DEFAULT NULL,
  isbn VARCHAR(250) DEFAULT NULL,
  url VARCHAR(500) DEFAULT NULL,
  PRIMARY KEY(referenceID)
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE source (
  sourceID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  referenceID INTEGER UNSIGNED DEFAULT NULL,
  sourceName VARCHAR(250) DEFAULT NULL UNIQUE,
  sourceUrl VARCHAR(500) DEFAULT NULL,
  dateAccessed DATE DEFAULT NULL,
  isHigherClassification INTEGER(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY(sourceID),
  INDEX source_FK_referenceID(referenceID),
  INDEX source_sourceName(sourceName),
  INDEX source_isHigherClassification(isHigherClassification),
  FOREIGN KEY(referenceID) REFERENCES reference(referenceID) ON DELETE  NO ACTION ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE name (
  nameID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  bestFuzzyMatchID INTEGER UNSIGNED DEFAULT NULL,
  originalSourceID INTEGER UNSIGNED DEFAULT NULL,
  nomenclaturalCode VARCHAR(25) DEFAULT NULL,
  scientificName VARCHAR(250) NOT NULL,
  scientificNameAuthorship VARCHAR(250) DEFAULT NULL,
  nameRank VARCHAR(25) DEFAULT NULL,
  nameParts INTEGER(1) DEFAULT NULL,
  namePublicationYear INTEGER UNSIGNED DEFAULT NULL,
  taxonomicStatus VARCHAR(250) DEFAULT NULL,
  taxonRemarks VARCHAR(250) DEFAULT NULL,
  namePublicationReferenceID INTEGER UNSIGNED DEFAULT NULL,
  scientificNameWithAuthor VARCHAR(250) NOT NULL,
  genusHybridX VARCHAR(1) DEFAULT NULL,
  genus VARCHAR(100) DEFAULT NULL,
  speciesHybridX VARCHAR(1) DEFAULT NULL,
  specificEpithet VARCHAR(100) DEFAULT NULL,
  rankIndicator VARCHAR(12) DEFAULT NULL COMMENT 'Rank abbreviation used to form name string, if applicable',
  infraspecificHybridX VARCHAR(1) DEFAULT NULL,
  infraspecificEpithet VARCHAR(100) DEFAULT NULL,
  infraspecificHybridX2 VARCHAR(1) DEFAULT NULL,
  infraspecificRank2 VARCHAR(15) DEFAULT NULL,
  infraspecificEpithet2 VARCHAR(100) DEFAULT NULL,
  otherEpithet VARCHAR(100) DEFAULT NULL COMMENT 'Epithets for tribe, section, etc.',
  isHybrid INT(1) NOT NULL DEFAULT 0,
  isNamedHybrid INT(1) DEFAULT NULL DEFAULT 0,
  isHybridFormula INT(1) DEFAULT NULL DEFAULT 0,
  PRIMARY KEY(nameID),
  INDEX name_bestFuzzyMatchID(bestFuzzyMatchID),
  INDEX name_originalSourceID(originalSourceID),
  INDEX name_nomenclaturalCode(nomenclaturalCode),
  INDEX name_FK1(namePublicationReferenceID),
  INDEX name_scientificName(scientificName),
  INDEX name_scientificNameAuthorship(scientificNameAuthorship),
  INDEX name_nameRank(nameRank),
  INDEX name_nameParts(nameParts),
  INDEX name_taxonomicStatus(taxonomicStatus),
  INDEX name_scientificNameWithAuthor(scientificNameWithAuthor),
  INDEX name_isHybrid(isHybrid),
  INDEX name_genus(genus),
  INDEX name_specificEpithet(specificEpithet),
  INDEX name_otherEpithet(otherEpithet),
  INDEX name_rankIndicator(rankIndicator),
  INDEX name_infraspecificEpithet(infraspecificEpithet),
  INDEX name_infraspecificRank2(infraspecificRank2),
  INDEX name_infraspecificEpithet2(infraspecificEpithet2),
  FOREIGN KEY(namePublicationReferenceID) REFERENCES reference(referenceID) ON DELETE NO ACTION ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE name_source (
  nameSourceID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  nameID INTEGER UNSIGNED NOT NULL,
  sourceID INTEGER UNSIGNED NOT NULL,
  nameSourceUrl VARCHAR(250) DEFAULT NULL,
  nameSourceOriginalID VARCHAR(250) DEFAULT NULL,
  dateAccessed DATE DEFAULT NULL,
  dateCreated TIMESTAMP NOT NULL,
  PRIMARY KEY(nameSourceID),
  INDEX nameSource_nameSourceOriginalID(nameSourceOriginalID),
  INDEX nameSource_FKIndex1(nameID),
  INDEX nameSource_FKIndex2(sourceID),
  FOREIGN KEY(nameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY(sourceID) REFERENCES source(sourceID) ON DELETE RESTRICT ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE classification (
  classificationID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  sourceID INTEGER UNSIGNED NOT NULL,
  nameID INTEGER UNSIGNED NOT NULL,
  parentNameID INTEGER UNSIGNED DEFAULT NULL,
  leftIndex INTEGER UNSIGNED DEFAULT NULL,
  rightIndex INTEGER UNSIGNED DEFAULT NULL,
  PRIMARY KEY(classificationID),
  INDEX classification_default_FKIndex1(parentNameID),
  INDEX classification_default_FKIndex2(nameID),
  INDEX classification_FKIndex3(sourceID),
  INDEX classification_leftIndex(leftIndex),
  INDEX classification_rightIndex(rightIndex),
  FOREIGN KEY(parentNameID) REFERENCES name(nameID) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY(nameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY(sourceID) REFERENCES source(sourceID) ON DELETE RESTRICT ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE `synonym` (
  synonymID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  sourceID INTEGER UNSIGNED NOT NULL,
  nameID INTEGER UNSIGNED NOT NULL,
  acceptedNameID INTEGER UNSIGNED DEFAULT NULL,
  acceptance VARCHAR(50) DEFAULT NULL,
  nomenclaturalStatus VARCHAR(100) DEFAULT NULL,
  synonymType VARCHAR(250) DEFAULT NULL,
  synonymSourceUrl VARCHAR(250) DEFAULT NULL,
  referenceID INTEGER UNSIGNED DEFAULT NULL,
  PRIMARY KEY(synonymID),
  INDEX synonym_acceptedNameID(acceptedNameID),
  INDEX synonym_acceptance(acceptance),
  INDEX synonym_nomenclaturalStatus(nomenclaturalStatus),
  INDEX synonym_nameID(nameID),
  INDEX synonym_sourceID(sourceID),
  INDEX synonym_referenceID(referenceID),
  INDEX synonym_synonymType(synonymType),
  FOREIGN KEY(nameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY(sourceID) REFERENCES source(sourceID) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY(referenceID) REFERENCES reference(referenceID) ON DELETE NO ACTION ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE lexicalGroup (
  lexicalGroupID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(lexicalGroupID)
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE name_lexicalGroup (
  nameID INTEGER UNSIGNED NOT NULL,
  lexicalGroupID INTEGER UNSIGNED NOT NULL,
  INDEX name_lexicalGroup_nameID(nameID),
  INDEX name_lexicalGroup_lexicalGroupID(lexicalGroupID),
  FOREIGN KEY(nameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY(lexicalGroupID) REFERENCES lexicalGroup(lexicalGroupID) ON DELETE CASCADE ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE fuzzyMatch (
  fuzzyMatchID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  nameID INTEGER UNSIGNED NOT NULL,
  matchedNameID INTEGER UNSIGNED NOT NULL,
  overallScore DECIMAL(4,3) DEFAULT NULL,
  taxonScore DECIMAL(4,3) DEFAULT NULL,
  authorScore DECIMAL(4,3) DEFAULT NULL,
  PRIMARY KEY(fuzzyMatchID),
  INDEX fuzzyMatch_nameID(nameID),
  INDEX fuzzyMatch_matchedNameID(matchedNameID),
  FOREIGN KEY(nameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY(matchedNameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

